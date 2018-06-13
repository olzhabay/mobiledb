#ifndef MOBILEDB_ENV_H
#define MOBILEDB_ENV_H


#include <stdint.h>
#include <sys/time.h>
#include <pthread.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "status.h"
#include "port.h"


struct FileLock {
    int fd_;
    std::string name_;
};

// Set of locked files.  We keep a separate set instead of just
// relying on fcntrl(F_SETLK) since fcntl(F_SETLK) does not provide
// any protection against multiple uses from the same process.
class LockTable {
private:
    Mutex mu_;
    std::set<std::string> locked_files_ GUARDED_BY(mu_);
public:
    bool Insert(const std::string& fname) LOCKS_EXCLUDED(mu_) {
            MutexLock l(&mu_);
            return locked_files_.insert(fname).second;
    }
    void Remove(const std::string& fname) LOCKS_EXCLUDED(mu_) {
            MutexLock l(&mu_);
            locked_files_.erase(fname);
    }
};

static Status PosixError(const std::string& context, int err_number) {
    if (err_number == ENOENT) {
        return Status::NotFound(context, strerror(err_number));
    } else {
        return Status::IOError(context, strerror(err_number));
    }
}

static int LockOrUnlock(int fd, bool lock) {
    errno = 0;
    struct flock f;
    memset(&f, 0, sizeof(f));
    f.l_type = (lock ? F_WRLCK : F_UNLCK);
    f.l_whence = SEEK_SET;
    f.l_start = 0;
    f.l_len = 0;        // Lock/unlock entire file
    return fcntl(fd, F_SETLK, &f);
}

class Env {
public:

    Status GetChildren(const std::string& dir,
                       std::vector<std::string>* result) {
        result->clear();
        DIR* d = opendir(dir.c_str());
        if (d == nullptr) {
            return PosixError(dir, errno);
        }
        struct dirent* entry;
        while ((entry = readdir(d)) != nullptr) {
            result->push_back(entry->d_name);
        }
        closedir(d);
        return Status::OK();
    }

    Status DeleteFile(const std::string& fname) {
        Status result;
        if (unlink(fname.c_str()) != 0) {
            result = PosixError(fname, errno);
        }
        return result;
    }


    Status CreateDir(const std::string& name) {
        Status result;
        if (mkdir(name.c_str(), 0755) != 0) {
            result = PosixError(name, errno);
        }
        return result;
    }

    Status DeleteDir(const std::string& name) {
        Status result;
        if (rmdir(name.c_str()) != 0) {
            result = PosixError(name, errno);
        }
        return result;
    }

    Status GetFileSize(const std::string& fname, uint64_t* size) {
        Status s;
        struct stat sbuf;
        if (stat(fname.c_str(), &sbuf) != 0) {
            *size = 0;
            s = PosixError(fname, errno);
        } else {
            *size = sbuf.st_size;
        }
        return s;
    }

    Status RenameFile(const std::string& src, const std::string& target) {
        Status result;
        if (rename(src.c_str(), target.c_str()) != 0) {
            result = PosixError(src, errno);
        }
        return result;
    }

    Status LockFile(const std::string& fname, FileLock** lock) {
        *lock = nullptr;
        Status result;
        int fd = open(fname.c_str(), O_RDWR | O_CREAT, 0644);
        if (fd < 0) {
            result = PosixError(fname, errno);
        } else if (!locks_.Insert(fname)) {
            close(fd);
            result = Status::IOError("lock " + fname, "already held by process");
        } else if (LockOrUnlock(fd, true) == -1) {
            result = PosixError("lock " + fname, errno);
            close(fd);
            locks_.Remove(fname);
        } else {
            FileLock* my_lock = new FileLock;
            my_lock->fd_ = fd;
            my_lock->name_ = fname;
            *lock = my_lock;
        }
        return result;
    }

    Status UnlockFile(FileLock* lock) {
        FileLock* my_lock = reinterpret_cast<FileLock*>(lock);
        Status result;
        if (LockOrUnlock(my_lock->fd_, false) == -1) {
            result = PosixError("unlock", errno);
        }
        locks_.Remove(my_lock->name_);
        close(my_lock->fd_);
        delete my_lock;
        return result;
    }

    Status GetTestDirectory(std::string* result) {
        const char* env = getenv("TEST_TMPDIR");
        if (env && env[0] != '\0') {
            *result = env;
        } else {
            char buf[100];
            snprintf(buf, sizeof(buf), "/tmp/dbtest-%d", int(geteuid()));
            *result = buf;
        }
        // Directory may already exist
        CreateDir(*result);
        return Status::OK();
    }

    void StartThread(void (*function)(void* arg), void* arg) {
        pthread_t t;
        StartThreadState* state = new StartThreadState;
        state->user_function = function;
        state->arg = arg;
        PthreadCall("start thread",
                    pthread_create(&t, nullptr,  &StartThreadWrapper, state));
    }

    uint64_t NowMicros() {
        struct timeval tv;
        gettimeofday(&tv, nullptr);
        return static_cast<uint64_t>(tv.tv_sec) * 1000000 + tv.tv_usec;
    }

    static Env* Default() {
        pthread_once(&once, InitDefaultEnv);
        return default_env;
    }

private:

    void PthreadCall(const char* label, int result) {
        if (result != 0) {
            fprintf(stderr, "pthread %s: %s\n", label, strerror(result));
            abort();
        }
    }

    struct StartThreadState {
        void (*user_function)(void*);
        void* arg;
    };

    static void* StartThreadWrapper(void* arg) {
        StartThreadState* state = reinterpret_cast<StartThreadState*>(arg);
        state->user_function(state->arg);
        delete state;
        return nullptr;
    }


    LockTable locks_;

    static pthread_once_t once = PTHREAD_ONCE_INIT;
    static void InitDefaultEnv() { default_env = new Env; }
    static Env* default_env;
};


#endif //MOBILEDB_ENV_H
