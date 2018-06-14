#ifndef MOBILEDB_BTREE_ITERATOR_HH
#define MOBILEDB_BTREE_ITERATOR_HH

#include "btree.hh"

class BtreeIterator {
public:
  BtreeIterator(Btree* b);

  bool Valid() const;

  void SeekToFirst();

  void SeekToLast();

  void Seek(const int64_t& key);

  void Next();

  void Prev();

  int64_t key() const;

  void* value() const;

private:
  Btree* btree;
  Entry* cur;
  Page* cur_page;
  int index;
  bool valid; // validity of current entry
};


#endif //MOBILEDB_BTREE_ITERATOR_HH
