#include "btree_iterator.hh"


BtreeIterator::BtreeIterator(Btree* b) {
  btree = b;
  SeekToFirst();
}

bool BtreeIterator::Valid() const {
  return valid;
}

void BtreeIterator::SeekToFirst() {
  Page* page = (Page*)btree->root;
  while(page->hdr.leftmost_ptr != NULL) {
    page = page->hdr.leftmost_ptr;
  }
  cur_page = page;
  cur = &(page->records[0]);
  index = 0;
  valid = cur != NULL;
}

void BtreeIterator::SeekToLast() {
  Page* page = (Page*)btree->root;
  while(page->hdr.leftmost_ptr != NULL) {
    page = page->hdr.leftmost_ptr;
  }
  while(page->hdr.sibling_ptr != NULL) {
    page = page->hdr.sibling_ptr;
  }
  cur_page = page;
  cur = &(cur_page->records[cur_page->count()-1]);
  index = cur_page->count()-1;
  valid = cur != NULL;
}

void BtreeIterator::Seek(const int64_t& key) {
  Page* page = (Page*)btree->root;
  // search until leaf node
  while(page->hdr.leftmost_ptr!=NULL) {
    page = (Page*)page->linear_search(key);
  }
  // TODO: Fix
  uint8_t previous_switch_counter;
  int i;
  Entry* ret = nullptr;
  do {
    do {
      previous_switch_counter = page->hdr.switch_counter;
      ret = nullptr;
      if (IS_FORWARD(previous_switch_counter)) {
        if (page->records[0].key == key && page->records[0].ptr != nullptr) {
          ret = &page->records[0];
          index = 0;
          continue;
        }
        for (i = 1; page->records[i].ptr != nullptr; ++i) {
          if (page->records[i].key == key && page->records[i].ptr != nullptr) {
            ret = &page->records[i];
            index = i;
            break;
          }
        }
      } else {
        for (i = page->count() - 1; i > 0; --i) {
          if (page->records[i].key == key && page->records[i].ptr != nullptr) {
            ret = &page->records[i];
            index = i;
            break;
          }
        }
        if (!ret) {
          if (page->records[0].key == key && page->records[0].ptr != nullptr) {
            ret = &page->records[0];
            index = 0;
            continue;
          }
        }
      }
    } while (page->hdr.switch_counter != previous_switch_counter);

    if (ret) {
      cur = ret;
      cur_page = page;
    }
  } while (page != page->hdr.sibling_ptr
           && (page = page->hdr.sibling_ptr)
           && key >= page->records[0].key);

  valid = (ret != nullptr) ? true : false;
}

void BtreeIterator::Next() {
  if(index == cur_page->count()-1) {
    if(cur_page->hdr.sibling_ptr != NULL) {
      cur_page = cur_page->hdr.sibling_ptr;
      cur = &(cur_page->records[0]);
      index = 0;
    }
  } else {
    index = index+1;
    cur = &(cur_page->records[index]);
  }
}

void BtreeIterator::Prev() {
  if(index == 0) {
  } else {
    index = index-1;
    cur = &(cur_page->records[index]);
  }
}

int64_t BtreeIterator::key() const {
  if(Valid()) {
    return cur->key;
  } else {
    return -1;
  }
}

void* BtreeIterator::value() const {
  if(Valid()) {
    return cur->ptr;
  } else {
    return nullptr;
  }
}
