#include "kv_store_iterator.hh"

bool KVStoreIterator::Valid() const {
  return btree_iterator->Valid();
}

void KVStoreIterator::SeekToFirst() {
  btree_iterator->SeekToFirst();
}

void KVStoreIterator::SeekToLast() {
  btree_iterator->SeekToLast();
}

void KVStoreIterator::Seek(const Slice& target) {
  int64_t key = fast_atoi(target.data(), target.size());
  btree_iterator->Seek(key);
}

void KVStoreIterator::Next() {
  btree_iterator->Next();
}

void KVStoreIterator::Prev() {
  btree_iterator->Prev();
}

Slice KVStoreIterator::key() const {
  char key[100];
  snprintf(key, sizeof(key), "%li", btree_iterator->key());
  return Slice(key);
}

Slice KVStoreIterator::value() const {
  return StorageManager::Get(btree_iterator->value());
}

Status KVStoreIterator::status() const {
  if (btree_iterator->Valid())
    return Status::OK();
  else
    return Status::Corruption("Some Problem");
}

KVStoreIterator::~KVStoreIterator() {
  delete btree_iterator;
}
