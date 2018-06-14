#ifndef MOBILEDB_DB_H
#define MOBILEDB_DB_H

#include "../common/status.hh"
#include "../common/slice.hh"
#include "../common/iterator.hh"
#include "storage_manager.hh"
#include "btree.hh"


class KVStore {
public:
    KVStore() = default;

    KVStore(const KVStore&) = delete;
    KVStore& operator=(const KVStore&) = delete;
    ~KVStore() = default;

    Status Put(const Slice& key, const Slice& value);
    Status Get(const Slice& key, Slice* value);
    Status Delete(const Slice& key);
    Iterator* NewIterator();

private:
  Btree btree;
};

#endif // MOBILEDB_DB_H
