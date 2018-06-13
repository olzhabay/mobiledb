// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include "common/db.h"
#include "common/env.h"
#include "common/slice.h"
#include "common/status.h"
#include "common/random.h"

// Comma-separated list of operations to run in the specified order
//   Actual benchmarks:
//      fillseq       -- write N values in sequential key order in async mode
//      fillrandom    -- write N values in random key order in async mode
//      fillsync      -- write N/100 values in random key order in sync mode
//      readseq       -- read N times sequentially
//      readrandom    -- read N times in random order
//      readmissing   -- read N missing keys in random order
//      readhot       -- read N times in random order from 1% section of DB
//      seekrandom    -- N random seeks

static const char* FLAGS_benchmarks =
        "fillseq,"
        "fillsync,"
        "fillrandom,"
        "overwrite,"
        "readrandom,"
        "readrandom,"  // Extra run to allow previous compactions to quiesce
        "readseq,"
        "readreverse,"
        "compact,"
        "readrandom,"
        "readseq,"
        "readreverse,"
        "fill100K,"
        "crc32c,"
        "snappycomp,"
        "snappyuncomp,"
        "acquireload,"
;

// Number of key/values to place in database
static int FLAGS_num = 1000000;

// Number of read operations to do.  If negative, do FLAGS_num reads.
static int FLAGS_reads = -1;

// Number of concurrent threads to run.
static int FLAGS_threads = 1;

// Size of each value
static int FLAGS_value_size = 100;

// Arrange to generate values that shrink to this fraction of
// their original size after compression
static double FLAGS_compression_ratio = 0.5;

// Print histogram of operation timings
static bool FLAGS_histogram = false;

// Number of bytes to buffer in memtable before compacting
// (initialized to default value by "main")
static int FLAGS_write_buffer_size = 0;

// Number of bytes written to each file.
// (initialized to default value by "main")
static int FLAGS_max_file_size = 0;

// Approximate size of user data packed per block (before compression.
// (initialized to default value by "main")
static int FLAGS_block_size = 0;

// Number of bytes to use as a cache of uncompressed data.
// Negative means use default settings.
static int FLAGS_cache_size = -1;

// Maximum number of files to keep open at the same time (use default if == 0)
static int FLAGS_open_files = 0;

// Bloom filter bits per key.
// Negative means use default settings.
static int FLAGS_bloom_bits = -1;

// Use the db with the following name.
static const char* FLAGS_db = nullptr;
namespace {
    Env* g_env = nullptr;

// Helper for quickly generating random data.
    class RandomGenerator {
    private:
        std::string data_;
        int pos_;

    public:
        RandomGenerator() {
            // We use a limited amount of data over and over again and ensure
            // that it is larger than the compression window (32KB), and also
            // large enough to serve all typical value sizes we want to write.
            Random rnd(301);
            std::string piece;
            while (data_.size() < 1048576) {
                // Add a short fragment that is as compressible as specified
                // by FLAGS_compression_ratio.
                test::CompressibleString(&rnd, FLAGS_compression_ratio, 100, &piece);
                data_.append(piece);
            }
            pos_ = 0;
        }

        Slice Generate(size_t len) {
            if (pos_ + len > data_.size()) {
                pos_ = 0;
                assert(len < data_.size());
            }
            pos_ += len;
            return Slice(data_.data() + pos_ - len, len);
        }
    };

#if defined(__linux)
    static Slice TrimSpace(Slice s) {
  size_t start = 0;
  while (start < s.size() && isspace(s[start])) {
    start++;
  }
  size_t limit = s.size();
  while (limit > start && isspace(s[limit-1])) {
    limit--;
  }
  return Slice(s.data() + start, limit - start);
}
#endif

    static void AppendWithSpace(std::string* str, Slice msg) {
        if (msg.empty()) return;
        if (!str->empty()) {
            str->push_back(' ');
        }
        str->append(msg.data(), msg.size());
    }

    class Stats {
    private:
        double start_;
        double finish_;
        double seconds_;
        int done_;
        int next_report_;
        int64_t bytes_;
        double last_op_finish_;
        std::string message_;

    public:
        Stats() { Start(); }

        void Start() {
            next_report_ = 100;
            last_op_finish_ = start_;
            done_ = 0;
            bytes_ = 0;
            seconds_ = 0;
            start_ = g_env->NowMicros();
            finish_ = start_;
            message_.clear();
        }

        void Merge(const Stats& other) {
            done_ += other.done_;
            bytes_ += other.bytes_;
            seconds_ += other.seconds_;
            if (other.start_ < start_) start_ = other.start_;
            if (other.finish_ > finish_) finish_ = other.finish_;

            // Just keep the messages from one thread
            if (message_.empty()) message_ = other.message_;
        }

        void Stop() {
            finish_ = g_env->NowMicros();
            seconds_ = (finish_ - start_) * 1e-6;
        }

        void AddMessage(Slice msg) {
            AppendWithSpace(&message_, msg);
        }

        void FinishedSingleOp() {
            if (FLAGS_histogram) {
                double now = g_env->NowMicros();
                double micros = now - last_op_finish_;
                if (micros > 20000) {
                    fprintf(stderr, "long op: %.1f micros%30s\r", micros, "");
                    fflush(stderr);
                }
                last_op_finish_ = now;
            }

            done_++;
            if (done_ >= next_report_) {
                if      (next_report_ < 1000)   next_report_ += 100;
                else if (next_report_ < 5000)   next_report_ += 500;
                else if (next_report_ < 10000)  next_report_ += 1000;
                else if (next_report_ < 50000)  next_report_ += 5000;
                else if (next_report_ < 100000) next_report_ += 10000;
                else if (next_report_ < 500000) next_report_ += 50000;
                else                            next_report_ += 100000;
                fprintf(stderr, "... finished %d ops%30s\r", done_, "");
                fflush(stderr);
            }
        }

        void AddBytes(int64_t n) {
            bytes_ += n;
        }

        void Report(const Slice& name) {
            // Pretend at least one op was done in case we are running a benchmark
            // that does not call FinishedSingleOp().
            if (done_ < 1) done_ = 1;

            std::string extra;
            if (bytes_ > 0) {
                // Rate is computed on actual elapsed time, not the sum of per-thread
                // elapsed times.
                double elapsed = (finish_ - start_) * 1e-6;
                char rate[100];
                snprintf(rate, sizeof(rate), "%6.1f MB/s",
                         (bytes_ / 1048576.0) / elapsed);
                extra = rate;
            }
            AppendWithSpace(&extra, message_);

            fprintf(stdout, "%-12s : %11.3f micros/op;%s%s\n",
                    name.ToString().c_str(),
                    seconds_ * 1e6 / done_,
                    (extra.empty() ? "" : " "),
                    extra.c_str());
            fflush(stdout);
        }
    };

// State shared by all concurrent executions of the same benchmark.
    struct SharedState {
        port::Mutex mu;
        port::CondVar cv GUARDED_BY(mu);
        int total GUARDED_BY(mu);

        // Each thread goes through the following states:
        //    (1) initializing
        //    (2) waiting for others to be initialized
        //    (3) running
        //    (4) done

        int num_initialized GUARDED_BY(mu);
        int num_done GUARDED_BY(mu);
        bool start GUARDED_BY(mu);

        SharedState(int total)
                : cv(&mu), total(total), num_initialized(0), num_done(0), start(false) { }
    };

// Per-thread state for concurrent executions of the same benchmark.
    struct ThreadState {
        int tid;             // 0..n-1 when running in n threads
        Random rand;         // Has different seeds for different threads
        Stats stats;
        SharedState* shared;

        ThreadState(int index)
                : tid(index),
                  rand(1000 + index) {
        }
    };

}  // namespace

class Benchmark {
private:
    DB* db_;
    int num_;
    int value_size_;
    int entries_per_batch_;
    int reads_;
    int heap_counter_;

    void PrintHeader() {
        const int kKeySize = 16;
        PrintEnvironment();
        fprintf(stdout, "Keys:       %d bytes each\n", kKeySize);
        fprintf(stdout, "Values:     %d bytes each (%d bytes after compression)\n",
                FLAGS_value_size,
                static_cast<int>(FLAGS_value_size * FLAGS_compression_ratio + 0.5));
        fprintf(stdout, "Entries:    %d\n", num_);
        fprintf(stdout, "RawSize:    %.1f MB (estimated)\n",
                ((static_cast<int64_t>(kKeySize + FLAGS_value_size) * num_)
                 / 1048576.0));
        fprintf(stdout, "FileSize:   %.1f MB (estimated)\n",
                (((kKeySize + FLAGS_value_size * FLAGS_compression_ratio) * num_)
                 / 1048576.0));
        PrintWarnings();
        fprintf(stdout, "------------------------------------------------\n");
    }

    void PrintWarnings() {
#if defined(__GNUC__) && !defined(__OPTIMIZE__)
        fprintf(stdout,
            "WARNING: Optimization is disabled: benchmarks unnecessarily slow\n"
            );
#endif
#ifndef NDEBUG
        fprintf(stdout,
                "WARNING: Assertions are enabled; benchmarks unnecessarily slow\n");
#endif
    }

    void PrintEnvironment() {

#if defined(__linux)
        time_t now = time(nullptr);
    fprintf(stderr, "Date:       %s", ctime(&now));  // ctime() adds newline

    FILE* cpuinfo = fopen("/proc/cpuinfo", "r");
    if (cpuinfo != nullptr) {
      char line[1000];
      int num_cpus = 0;
      std::string cpu_type;
      std::string cache_size;
      while (fgets(line, sizeof(line), cpuinfo) != nullptr) {
        const char* sep = strchr(line, ':');
        if (sep == nullptr) {
          continue;
        }
        Slice key = TrimSpace(Slice(line, sep - 1 - line));
        Slice val = TrimSpace(Slice(sep + 1));
        if (key == "model name") {
          ++num_cpus;
          cpu_type = val.ToString();
        } else if (key == "cache size") {
          cache_size = val.ToString();
        }
      }
      fclose(cpuinfo);
      fprintf(stderr, "CPU:        %d * %s\n", num_cpus, cpu_type.c_str());
      fprintf(stderr, "CPUCache:   %s\n", cache_size.c_str());
    }
#endif
    }

public:
    Benchmark()
            : db_(nullptr),
              num_(FLAGS_num),
              value_size_(FLAGS_value_size),
              entries_per_batch_(1),
              reads_(FLAGS_reads < 0 ? FLAGS_num : FLAGS_reads),
              heap_counter_(0) {
        std::vector<std::string> files;
        g_env->GetChildren(FLAGS_db, &files);
        for (size_t i = 0; i < files.size(); i++) {
            if (Slice(files[i]).starts_with("heap-")) {
                g_env->DeleteFile(std::string(FLAGS_db) + "/" + files[i]);
            }
        }
        if (!FLAGS_use_existing_db) {
            DestroyDB(FLAGS_db, Options());
        }
    }

    ~Benchmark() {
        delete db_;
    }

    void Run() {
        PrintHeader();
        Open();

        const char* benchmarks = FLAGS_benchmarks;
        while (benchmarks != nullptr) {
            const char* sep = strchr(benchmarks, ',');
            Slice name;
            if (sep == nullptr) {
                name = benchmarks;
                benchmarks = nullptr;
            } else {
                name = Slice(benchmarks, sep - benchmarks);
                benchmarks = sep + 1;
            }

            // Reset parameters that may be overridden below
            num_ = FLAGS_num;
            reads_ = (FLAGS_reads < 0 ? FLAGS_num : FLAGS_reads);
            value_size_ = FLAGS_value_size;
            entries_per_batch_ = 1;

            void (Benchmark::*method)(ThreadState*) = nullptr;
            bool fresh_db = false;
            int num_threads = FLAGS_threads;

            if (name == Slice("fillseq")) {
                fresh_db = true;
                method = &Benchmark::WriteSeq;
            } else if (name == Slice("fillbatch")) {
                fresh_db = true;
                entries_per_batch_ = 1000;
                method = &Benchmark::WriteSeq;
            } else if (name == Slice("fillrandom")) {
                fresh_db = true;
                method = &Benchmark::WriteRandom;
            } else if (name == Slice("overwrite")) {
                fresh_db = false;
                method = &Benchmark::WriteRandom;
            } else if (name == Slice("fillsync")) {
                fresh_db = true;
                num_ /= 1000;
                method = &Benchmark::WriteRandom;
            } else if (name == Slice("readseq")) {
                method = &Benchmark::ReadSequential;
            } else if (name == Slice("readrandom")) {
                method = &Benchmark::ReadRandom;
            } else if (name == Slice("seekrandom")) {
                method = &Benchmark::SeekRandom;
            } else {
                if (name != Slice()) {  // No error message for empty name
                    fprintf(stderr, "unknown benchmark '%s'\n", name.ToString().c_str());
                }
            }

            if (method != nullptr) {
                RunBenchmark(num_threads, name, method);
            }
        }
    }

private:
    struct ThreadArg {
        Benchmark* bm;
        SharedState* shared;
        ThreadState* thread;
        void (Benchmark::*method)(ThreadState*);
    };

    static void ThreadBody(void* v) {
        ThreadArg* arg = reinterpret_cast<ThreadArg*>(v);
        SharedState* shared = arg->shared;
        ThreadState* thread = arg->thread;
        {
            MutexLock l(&shared->mu);
            shared->num_initialized++;
            if (shared->num_initialized >= shared->total) {
                shared->cv.SignalAll();
            }
            while (!shared->start) {
                shared->cv.Wait();
            }
        }

        thread->stats.Start();
        (arg->bm->*(arg->method))(thread);
        thread->stats.Stop();

        {
            MutexLock l(&shared->mu);
            shared->num_done++;
            if (shared->num_done >= shared->total) {
                shared->cv.SignalAll();
            }
        }
    }

    void RunBenchmark(int n, Slice name,
                      void (Benchmark::*method)(ThreadState*)) {
        SharedState shared(n);

        ThreadArg* arg = new ThreadArg[n];
        for (int i = 0; i < n; i++) {
            arg[i].bm = this;
            arg[i].method = method;
            arg[i].shared = &shared;
            arg[i].thread = new ThreadState(i);
            arg[i].thread->shared = &shared;
            g_env->StartThread(ThreadBody, &arg[i]);
        }

        shared.mu.Lock();
        while (shared.num_initialized < n) {
            shared.cv.Wait();
        }

        shared.start = true;
        shared.cv.SignalAll();
        while (shared.num_done < n) {
            shared.cv.Wait();
        }
        shared.mu.Unlock();

        for (int i = 1; i < n; i++) {
            arg[0].thread->stats.Merge(arg[i].thread->stats);
        }
        arg[0].thread->stats.Report(name);

        for (int i = 0; i < n; i++) {
            delete arg[i].thread;
        }
        delete[] arg;
    }

    void Open() {
    }

    void WriteSeq(ThreadState* thread) {
        DoWrite(thread, true);
    }

    void WriteRandom(ThreadState* thread) {
        DoWrite(thread, false);
    }

    void DoWrite(ThreadState* thread, bool seq) {
        if (num_ != FLAGS_num) {
            char msg[100];
            snprintf(msg, sizeof(msg), "(%d ops)", num_);
            thread->stats.AddMessage(msg);
        }

        RandomGenerator gen;
        Status s;
        int64_t bytes = 0;
        for (int i = 0; i < num_; i += entries_per_batch_) {
            batch.Clear();
            for (int j = 0; j < entries_per_batch_; j++) {
                const int k = seq ? i+j : (thread->rand.Next() % FLAGS_num);
                char key[100];
                snprintf(key, sizeof(key), "%016d", k);
                batch.Put(key, gen.Generate(value_size_));
                bytes += value_size_ + strlen(key);
                thread->stats.FinishedSingleOp();
            }
            s = db_->Write(write_options_, &batch);
            if (!s.ok()) {
                fprintf(stderr, "put error: %s\n", s.ToString().c_str());
                exit(1);
            }
        }
        thread->stats.AddBytes(bytes);
    }

    void ReadSequential(ThreadState* thread) {
        Iterator* iter = db_->NewIterator(ReadOptions());
        int i = 0;
        int64_t bytes = 0;
        for (iter->SeekToFirst(); i < reads_ && iter->Valid(); iter->Next()) {
            bytes += iter->key().size() + iter->value().size();
            thread->stats.FinishedSingleOp();
            ++i;
        }
        delete iter;
        thread->stats.AddBytes(bytes);
    }

    void ReadRandom(ThreadState* thread) {
        std::string value;
        int found = 0;
        for (int i = 0; i < reads_; i++) {
            char key[100];
            const int k = thread->rand.Next() % FLAGS_num;
            snprintf(key, sizeof(key), "%016d", k);
            if (db_->Get(key, &value).ok()) {
                found++;
            }
            thread->stats.FinishedSingleOp();
        }
        char msg[100];
        snprintf(msg, sizeof(msg), "(%d of %d found)", found, num_);
        thread->stats.AddMessage(msg);
    }

    void SeekRandom(ThreadState* thread) {
        int found = 0;
        for (int i = 0; i < reads_; i++) {
            Iterator* iter = db_->NewIterator(options);
            char key[100];
            const int k = thread->rand.Next() % FLAGS_num;
            snprintf(key, sizeof(key), "%016d", k);
            iter->Seek(key);
            if (iter->Valid() && iter->key() == key) found++;
            delete iter;
            thread->stats.FinishedSingleOp();
        }
        char msg[100];
        snprintf(msg, sizeof(msg), "(%d of %d found)", found, num_);
        thread->stats.AddMessage(msg);
    }
};

int main(int argc, char** argv) {
    std::string default_db_path;

    for (int i = 1; i < argc; i++) {
        double d;
        int n;
        char junk;
        if (Slice(argv[i]).starts_with("--benchmarks=")) {
            FLAGS_benchmarks = argv[i] + strlen("--benchmarks=");
        } else if (sscanf(argv[i], "--num=%d%c", &n, &junk) == 1) {
            FLAGS_num = n;
        } else if (sscanf(argv[i], "--reads=%d%c", &n, &junk) == 1) {
            FLAGS_reads = n;
        } else if (sscanf(argv[i], "--value_size=%d%c", &n, &junk) == 1) {
            FLAGS_value_size = n;
        } else if (strncmp(argv[i], "--db=", 5) == 0) {
            FLAGS_db = argv[i] + 5;
        } else {
            fprintf(stderr, "Invalid flag '%s'\n", argv[i]);
            exit(1);
        }
    }

    g_env = Env::Default();

    // Choose a location for the test database if none given with --db=<path>
    if (FLAGS_db == nullptr) {
        g_env->GetTestDirectory(&default_db_path);
        default_db_path += "/dbbench";
        FLAGS_db = default_db_path.c_str();
    }

    Benchmark benchmark;
    benchmark.Run();
    return 0;
}