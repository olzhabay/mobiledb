// Copyright (c) 2018 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#ifndef MOBILEDB_PORT_H
#define MOBILEDB_PORT_H

#include <stddef.h>
#include <stdint.h>
#include <assert.h>
#include <condition_variable>  // NOLINT
#include <mutex>               // NOLINT
#include <string>
#include "thread_annotations.h"

class CondVar;

// Thinly wraps std::mutex.
class Mutex {
public:
    Mutex() = default;
    ~Mutex() = default;

    Mutex(const Mutex&) = delete;
    Mutex& operator=(const Mutex&) = delete;

    void Lock() EXCLUSIVE_LOCK_FUNCTION() { mu_.lock(); }
    void Unlock() UNLOCK_FUNCTION() { mu_.unlock(); }
    void AssertHeld() ASSERT_EXCLUSIVE_LOCK() { }

private:
    friend class CondVar;
    std::mutex mu_;
};

// Thinly wraps std::condition_variable.
class CondVar {
public:
    explicit CondVar(Mutex* mu) : mu_(mu) { assert(mu != nullptr); }
    ~CondVar() = default;

    CondVar(const CondVar&) = delete;
    CondVar& operator=(const CondVar&) = delete;

    void Wait() {
        std::unique_lock<std::mutex> lock(mu_->mu_, std::adopt_lock);
        cv_.wait(lock);
        lock.release();
    }
    void Signal() { cv_.notify_one(); }
    void SignalAll() { cv_.notify_all(); }
private:
    std::condition_variable cv_;
    Mutex* const mu_;
};


class SCOPED_LOCKABLE MutexLock {
public:
    explicit MutexLock(Mutex *mu) EXCLUSIVE_LOCK_FUNCTION(mu)
            : mu_(mu)  {
        this->mu_->Lock();
    }
    ~MutexLock() UNLOCK_FUNCTION() { this->mu_->Unlock(); }

private:
    Mutex *const mu_;
    // No copying allowed
    MutexLock(const MutexLock&);
    void operator=(const MutexLock&);
};

#endif //MOBILEDB_PORT_H
