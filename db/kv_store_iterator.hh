#ifndef MOBILEDB_KV_STORE_ITERATOR_HH
#define MOBILEDB_KV_STORE_ITERATOR_HH

#include "../common/iterator.hh"
#include "btree_iterator.hh"

class KVStoreIterator : public Iterator {
public:
  explicit KVStoreIterator(Btree* btree) : btree_iterator(new BtreeIterator(btree)) { }

  ~KVStoreIterator() override;

  bool Valid() const override;

  void SeekToFirst() override;

  void SeekToLast() override;

  void Seek(const Slice& target) override;

  void Next() override;

  void Prev() override;

  Slice key() const override;

  Slice value() const override;

  Status status() const override;

private:
  BtreeIterator* btree_iterator;
};


#endif //MOBILEDB_KV_STORE_ITERATOR_HH
