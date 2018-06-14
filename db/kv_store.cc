#include "kv_store.hh"
#include "kv_store_iterator.hh"

Status KVStore::Put(const Slice& key, const Slice& value) {
  void* ptr = StorageManager::Store(value);
  int k = atoi(key.data());
  btree.Insert(k, (char*) ptr);
  return Status::OK();
}

Status KVStore::Get(const Slice& key, Slice* value) {
  int k = atoi(key.data());
  void* ptr = btree.Search(k);
  if (ptr != nullptr) {
    value = new Slice(StorageManager::Get(ptr));
    return Status::OK();
  } else {
    return Status::NotFound("Not found");
  }
}

Status KVStore::Delete(const Slice& key) {
}

Iterator* KVStore::NewIterator() {
  return new KVStoreIterator(&btree);
}
