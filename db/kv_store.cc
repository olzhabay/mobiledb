#include "kv_store.hh"


Status KVStore::Put(const Slice& key, const Slice& value) {
  return Status();
}

Status KVStore::Get(const Slice& key, std::string* value) {
  return Status();
}

Status KVStore::Delete(const Slice& key) {
  return Status();
}

Iterator* KVStore::NewIterator() {
  return nullptr;
}
