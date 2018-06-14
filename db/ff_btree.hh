#ifndef MOBILEDB_FF_BTREE_HH
#define MOBILEDB_FF_BTREE_HH


#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <cassert>
#include <climits>
#include <future>
#include <mutex>
#include "../common/persist.hh"

#define IS_FORWARD(c) (c % 2 == 0)

using entry_key_t = int64_t;

using namespace std;

class Page;

class FFBtree {
private:
  int height;
  char* root;

  void setNewRoot(char* new_root);
  // store the key into the node at the given level
  void InsertInternal(char* left, entry_key_t key, char* right, uint32_t level);
  void RemoveInternal(entry_key_t left, char* ptr, uint32_t level,
                      entry_key_t* deleted_key, bool* is_leftmost_node, Page** left_sibling);

public:
  FFBtree();
// insert the key in the leaf node
  void Insert(entry_key_t key, char* right);
  void Remove(entry_key_t key);
  char* Search(entry_key_t key);
// Function to Search keys from "min" to "max"
  void Range(entry_key_t min, entry_key_t max, unsigned long* buf);

  friend class Page;
};

class Header {
private:
  Page* leftmost_ptr;         // 8 bytes
  Page* sibling_ptr;          // 8 bytes
  uint32_t level;             // 4 bytes
  uint8_t switch_counter;     // 1 bytes
  uint8_t is_deleted;         // 1 bytes
  int16_t last_index;         // 2 bytes
  char dummy[8];              // 8 bytes

  friend class Page;
  friend class FFBtree;

public:
  Header() {
    leftmost_ptr = NULL;
    sibling_ptr = NULL;
    switch_counter = 0;
    last_index = -1;
    is_deleted = false;
  }

  ~Header() {
  }
};

class Entry {
private:
  entry_key_t key; // 8 bytes
  char* ptr; // 8 bytes
public :
  Entry() {
    key = LONG_MAX;
    ptr = NULL;
  }

  friend class Page;
  friend class FFBtree;
};

const int cardinality = (PAGESIZE - sizeof(Header)) / sizeof(Entry);
const int count_in_line = CACHE_LINE_SIZE / sizeof(Entry);

class Page {
private:
  Header hdr;  // header in persistent memory, 16 bytes
  Entry records[cardinality]; // slots in persistent memory, 16 bytes * n

public:
  friend class FFBtree;

  Page(uint32_t level = 0) {
    hdr.level = level;
    records[0].ptr = NULL;
  }

  // this is called when tree grows
  Page(Page* left, entry_key_t key, Page* right, uint32_t level = 0) {
    hdr.leftmost_ptr = left;
    hdr.level = level;
    records[0].key = key;
    records[0].ptr = (char*) right;
    records[1].ptr = NULL;

    hdr.last_index = 0;

    clflush((char*) this, sizeof(Page));
  }

  void* operator new(size_t size) {
    void* ret;
    return posix_memalign(&ret, 64, size) == 0 ? ret : nullptr;
  }

  void operator delete(void* buffer) {
    free(buffer);
  }

  inline int count() {
    uint8_t previous_switch_counter;
    int count = 0;
    do {
      previous_switch_counter = hdr.switch_counter;
      count = hdr.last_index + 1;

      while (count >= 0 && records[count].ptr != NULL) {
        if (IS_FORWARD(previous_switch_counter))
          ++count;
        else
          --count;
      }

      if (count < 0) {
        count = 0;
        while (records[count].ptr != NULL) {
          ++count;
        }
      }

    } while (previous_switch_counter != hdr.switch_counter);

    return count;
  }

  inline bool remove_key(entry_key_t key) {
    // Set the switch_counter
    if (IS_FORWARD(hdr.switch_counter))
      ++hdr.switch_counter;

    bool shift = false;
    int i;
    for (i = 0; records[i].ptr != NULL; ++i) {
      if (!shift && records[i].key == key) {
        records[i].ptr = (i == 0) ?
                         (char*) hdr.leftmost_ptr : records[i - 1].ptr;
        shift = true;
      }

      if (shift) {
        records[i].key = records[i + 1].key;
        records[i].ptr = records[i + 1].ptr;

        // flush
        uint64_t records_ptr = (uint64_t) (&records[i]);
        int remainder = records_ptr % CACHE_LINE_SIZE;
        bool do_flush = (remainder == 0) ||
                        ((((int) (remainder + sizeof(Entry)) / CACHE_LINE_SIZE) == 1) &&
                         ((remainder + sizeof(Entry)) % CACHE_LINE_SIZE) != 0);
        if (do_flush) {
          clflush((char*) records_ptr, CACHE_LINE_SIZE);
        }
      }
    }

    if (shift) {
      --hdr.last_index;
    }
    return shift;
  }

  bool remove(FFBtree* bt, entry_key_t key, bool only_rebalance = false, bool with_lock = true) {
    if (!only_rebalance) {
      register int num_entries_before = count();

      // This node is root
      if (this == (Page*) bt->root) {
        if (hdr.level > 0) {
          if (num_entries_before == 1 && !hdr.sibling_ptr) {
            bt->root = (char*) hdr.leftmost_ptr;
            clflush((char*) &(bt->root), sizeof(char*));

            hdr.is_deleted = 1;
          }
        }

        // Remove the key from this node
        bool ret = remove_key(key);
        return true;
      }

      bool should_rebalance = true;
      // check the node utilization
      if (num_entries_before - 1 >= (int) ((cardinality - 1) * 0.5)) {
        should_rebalance = false;
      }

      // Remove the key from this node
      bool ret = remove_key(key);

      if (!should_rebalance) {
        return (hdr.leftmost_ptr == NULL) ? ret : true;
      }
    }

    //Remove a key from the parent node
    entry_key_t deleted_key_from_parent = 0;
    bool is_leftmost_node = false;
    Page* left_sibling;
    bt->RemoveInternal(key, (char*) this, hdr.level + 1,
                       &deleted_key_from_parent, &is_leftmost_node, &left_sibling);

    if (is_leftmost_node) {
      hdr.sibling_ptr->remove(bt, hdr.sibling_ptr->records[0].key, true,
                              with_lock);
      return true;
    }

    register int num_entries = count();
    register int left_num_entries = left_sibling->count();

    // Merge or Redistribution
    int total_num_entries = num_entries + left_num_entries;
    if (hdr.leftmost_ptr)
      ++total_num_entries;

    entry_key_t parent_key;

    if (total_num_entries > cardinality - 1) { // Redistribution
      register int m = (int) ceil(total_num_entries / 2);

      if (num_entries < left_num_entries) { // left -> right
        if (hdr.leftmost_ptr == nullptr) {
          for (int i = left_num_entries - 1; i >= m; i--) {
            insert_key
              (left_sibling->records[i].key, left_sibling->records[i].ptr, &num_entries);
          }

          left_sibling->records[m].ptr = nullptr;
          clflush((char*) &(left_sibling->records[m].ptr), sizeof(char*));

          left_sibling->hdr.last_index = m - 1;
          clflush((char*) &(left_sibling->hdr.last_index), sizeof(int16_t));

          parent_key = records[0].key;
        } else {
          insert_key(deleted_key_from_parent, (char*) hdr.leftmost_ptr,
                     &num_entries);

          for (int i = left_num_entries - 1; i > m; i--) {
            insert_key
              (left_sibling->records[i].key, left_sibling->records[i].ptr, &num_entries);
          }

          parent_key = left_sibling->records[m].key;

          hdr.leftmost_ptr = (Page*) left_sibling->records[m].ptr;
          clflush((char*) &(hdr.leftmost_ptr), sizeof(Page*));

          left_sibling->records[m].ptr = nullptr;
          clflush((char*) &(left_sibling->records[m].ptr), sizeof(char*));

          left_sibling->hdr.last_index = m - 1;
          clflush((char*) &(left_sibling->hdr.last_index), sizeof(int16_t));
        }

        if (left_sibling == ((Page*) bt->root)) {
          Page* new_root = new Page(left_sibling, parent_key, this, hdr.level + 1);
          bt->setNewRoot((char*) new_root);
        } else {
          bt->InsertInternal
            ((char*) left_sibling, parent_key, (char*) this, hdr.level + 1);
        }
      } else { // from leftmost case
        hdr.is_deleted = 1;
        clflush((char*) &(hdr.is_deleted), sizeof(uint8_t));

        Page* new_sibling = new Page(hdr.level);
        new_sibling->hdr.sibling_ptr = hdr.sibling_ptr;

        int num_dist_entries = num_entries - m;
        int new_sibling_cnt = 0;

        if (hdr.leftmost_ptr == nullptr) {
          for (int i = 0; i < num_dist_entries; i++) {
            left_sibling->insert_key(records[i].key, records[i].ptr,
                                     &left_num_entries);
          }

          for (int i = num_dist_entries; records[i].ptr != NULL; i++) {
            new_sibling->insert_key(records[i].key, records[i].ptr,
                                    &new_sibling_cnt, false);
          }

          clflush((char*) (new_sibling), sizeof(Page));

          left_sibling->hdr.sibling_ptr = new_sibling;
          clflush((char*) &(left_sibling->hdr.sibling_ptr), sizeof(Page*));

          parent_key = new_sibling->records[0].key;
        } else {
          left_sibling->insert_key(deleted_key_from_parent,
                                   (char*) hdr.leftmost_ptr, &left_num_entries);

          for (int i = 0; i < num_dist_entries - 1; i++) {
            left_sibling->insert_key(records[i].key, records[i].ptr,
                                     &left_num_entries);
          }

          parent_key = records[num_dist_entries - 1].key;

          new_sibling->hdr.leftmost_ptr = (Page*) records[num_dist_entries - 1].ptr;
          for (int i = num_dist_entries; records[i].ptr != NULL; i++) {
            new_sibling->insert_key(records[i].key, records[i].ptr,
                                    &new_sibling_cnt, false);
          }
          clflush((char*) (new_sibling), sizeof(Page));

          left_sibling->hdr.sibling_ptr = new_sibling;
          clflush((char*) &(left_sibling->hdr.sibling_ptr), sizeof(Page*));
        }

        if (left_sibling == ((Page*) bt->root)) {
          Page* new_root = new Page(left_sibling, parent_key, new_sibling, hdr.level + 1);
          bt->setNewRoot((char*) new_root);
        } else {
          bt->InsertInternal
            ((char*) left_sibling, parent_key, (char*) new_sibling, hdr.level + 1);
        }
      }
    } else {
      hdr.is_deleted = 1;
      clflush((char*) &(hdr.is_deleted), sizeof(uint8_t));
      if (hdr.leftmost_ptr)
        left_sibling->insert_key(deleted_key_from_parent,
                                 (char*) hdr.leftmost_ptr, &left_num_entries);

      for (int i = 0; records[i].ptr != NULL; ++i) {
        left_sibling->insert_key(records[i].key, records[i].ptr, &left_num_entries);
      }

      left_sibling->hdr.sibling_ptr = hdr.sibling_ptr;
      clflush((char*) &(left_sibling->hdr.sibling_ptr), sizeof(Page*));
    }

    return true;
  }

  inline void
  insert_key(entry_key_t key, char* ptr, int* num_entries, bool flush = true,
             bool update_last_index = true) {
    // update switch_counter
    if (!IS_FORWARD(hdr.switch_counter))
      ++hdr.switch_counter;

    // FAST
    if (*num_entries == 0) {  // this page is empty
      Entry* new_entry = (Entry*) &records[0];
      Entry* array_end = (Entry*) &records[1];
      new_entry->key = (entry_key_t) key;
      new_entry->ptr = (char*) ptr;

      array_end->ptr = (char*) NULL;

      if (flush) {
        clflush((char*) this, CACHE_LINE_SIZE);
      }
    } else {
      int i = *num_entries - 1, inserted = 0, to_flush_cnt = 0;
      records[*num_entries + 1].ptr = records[*num_entries].ptr;
      if (flush) {
        if ((uint64_t) &(records[*num_entries + 1].ptr) % CACHE_LINE_SIZE == 0)
          clflush((char*) &(records[*num_entries + 1].ptr), sizeof(char*));
      }

      // check for duplicate key
      for (i = *num_entries - 1; i >=0; i--) {
        if (key == records[i].key) {
          records[i].ptr = ptr;
          if (flush) {
            clflush((char*) &records[0], sizeof(Entry));
          }
          return;
        }
      }

      // FAST
      for (i = *num_entries - 1; i >= 0; i--) {
        if (key < records[i].key) {
          records[i + 1].ptr = records[i].ptr;
          records[i + 1].key = records[i].key;

          if (flush) {
            uint64_t records_ptr = (uint64_t) (&records[i + 1]);

            int remainder = records_ptr % CACHE_LINE_SIZE;
            bool do_flush = (remainder == 0) ||
                            ((((int) (remainder + sizeof(Entry)) / CACHE_LINE_SIZE) == 1)
                             && ((remainder + sizeof(Entry)) % CACHE_LINE_SIZE) != 0);
            if (do_flush) {
              clflush((char*) records_ptr, CACHE_LINE_SIZE);
              to_flush_cnt = 0;
            } else
              ++to_flush_cnt;
          }
        } else {
          records[i + 1].ptr = records[i].ptr;
          records[i + 1].key = key;
          records[i + 1].ptr = ptr;

          if (flush)
            clflush((char*) &records[i + 1], sizeof(Entry));
          inserted = 1;
          break;
        }
      }
      if (inserted == 0) {
        records[0].ptr = (char*) hdr.leftmost_ptr;
        records[0].key = key;
        records[0].ptr = ptr;
        if (flush)
          clflush((char*) &records[0], sizeof(Entry));
      }
    }

    if (update_last_index) {
      hdr.last_index = *num_entries;
    }
    ++(*num_entries);
  }

  // Insert a new key - FAST and FAIR
  Page* store
    (FFBtree* bt, char* left, entry_key_t key, char* right,
     bool flush, Page* invalid_sibling = NULL) {
    // If this node has a sibling node,
    if (hdr.sibling_ptr && (hdr.sibling_ptr != invalid_sibling)) {
      // Compare this key with the first key of the sibling
      if (key > hdr.sibling_ptr->records[0].key) {
        return hdr.sibling_ptr->store(bt, NULL, key, right,
                                      true, invalid_sibling);
      }
    }

    register int num_entries = count();

    // FAST
    if (num_entries < cardinality - 1) {
      insert_key(key, right, &num_entries, flush);
      return this;
    } else {// FAIR
      // overflow
      // create a new node
      Page* sibling = new Page(hdr.level);
      register int m = (int) ceil(num_entries / 2);
      entry_key_t split_key = records[m].key;

      // migrate half of keys into the sibling
      int sibling_cnt = 0;
      if (hdr.leftmost_ptr == NULL) { // leaf node
        for (int i = m; i < num_entries; ++i) {
          sibling->insert_key(records[i].key, records[i].ptr, &sibling_cnt, false);
        }
      } else { // internal node
        for (int i = m + 1; i < num_entries; ++i) {
          sibling->insert_key(records[i].key, records[i].ptr, &sibling_cnt, false);
        }
        sibling->hdr.leftmost_ptr = (Page*) records[m].ptr;
      }

      sibling->hdr.sibling_ptr = hdr.sibling_ptr;
      clflush((char*) sibling, sizeof(Page));

      hdr.sibling_ptr = sibling;
      clflush((char*) &hdr, sizeof(hdr));

      // set to NULL
      if (IS_FORWARD(hdr.switch_counter))
        hdr.switch_counter += 2;
      else
        ++hdr.switch_counter;
      records[m].ptr = NULL;
      clflush((char*) &records[m], sizeof(Entry));

      hdr.last_index = m - 1;
      clflush((char*) &(hdr.last_index), sizeof(int16_t));

      num_entries = hdr.last_index + 1;

      Page* ret;

      // insert the key
      if (key < split_key) {
        insert_key(key, right, &num_entries);
        ret = this;
      } else {
        sibling->insert_key(key, right, &sibling_cnt);
        ret = sibling;
      }

      // Set a new root or insert the split key to the parent
      if (bt->root == (char*) this) { // only one node can update the root ptr
        Page* new_root = new Page((Page*) this, split_key, sibling,
                                  hdr.level + 1);
        bt->setNewRoot((char*) new_root);
      } else {
        bt->InsertInternal(NULL, split_key, (char*) sibling,
                           hdr.level + 1);
      }

      return ret;
    }
  }

  // Search keys with linear Search
  void linear_search_range
    (entry_key_t min, entry_key_t max, unsigned long* buf) {
    int i, off = 0;
    uint8_t previous_switch_counter;
    Page* current = this;

    while (current) {
      int old_off = off;
      do {
        previous_switch_counter = current->hdr.switch_counter;
        off = old_off;

        entry_key_t tmp_key;
        char* tmp_ptr;

        if (IS_FORWARD(previous_switch_counter)) {
          if ((tmp_key = current->records[0].key) > min) {
            if (tmp_key < max) {
              if ((tmp_ptr = current->records[0].ptr) != NULL) {
                if (tmp_key == current->records[0].key) {
                  if (tmp_ptr) {
                    buf[off++] = (unsigned long) tmp_ptr;
                  }
                }
              }
            } else
              return;
          }

          for (i = 1; current->records[i].ptr != NULL; ++i) {
            if ((tmp_key = current->records[i].key) > min) {
              if (tmp_key < max) {
                if ((tmp_ptr = current->records[i].ptr) != current->records[i - 1].ptr) {
                  if (tmp_key == current->records[i].key) {
                    if (tmp_ptr)
                      buf[off++] = (unsigned long) tmp_ptr;
                  }
                }
              } else
                return;
            }
          }
        } else {
          for (i = count() - 1; i > 0; --i) {
            if ((tmp_key = current->records[i].key) > min) {
              if (tmp_key < max) {
                if ((tmp_ptr = current->records[i].ptr) != current->records[i - 1].ptr) {
                  if (tmp_key == current->records[i].key) {
                    if (tmp_ptr)
                      buf[off++] = (unsigned long) tmp_ptr;
                  }
                }
              } else
                return;
            }
          }

          if ((tmp_key = current->records[0].key) > min) {
            if (tmp_key < max) {
              if ((tmp_ptr = current->records[0].ptr) != NULL) {
                if (tmp_key == current->records[0].key) {
                  if (tmp_ptr) {
                    buf[off++] = (unsigned long) tmp_ptr;
                  }
                }
              }
            } else
              return;
          }
        }
      } while (previous_switch_counter != current->hdr.switch_counter);

      current = current->hdr.sibling_ptr;
    }
  }

  char* linear_search(entry_key_t key) {
    int i = 1;
    uint8_t previous_switch_counter;
    char* ret = NULL;
    char* t;
    entry_key_t k;

    if (hdr.leftmost_ptr == NULL) { // Search a leaf node
      do {
        previous_switch_counter = hdr.switch_counter;
        ret = NULL;

        // Search from left ro right
        if (IS_FORWARD(previous_switch_counter)) {
          if ((k = records[0].key) == key) {
            if ((t = records[0].ptr) != NULL) {
              if (k == records[0].key) {
                ret = t;
                continue;
              }
            }
          }

          for (i = 1; records[i].ptr != NULL; ++i) {
            if ((k = records[i].key) == key) {
              if (records[i - 1].ptr != (t = records[i].ptr)) {
                if (k == records[i].key) {
                  ret = t;
                  break;
                }
              }
            }
          }
        } else { // Search from right to left
          for (i = count() - 1; i > 0; --i) {
            if ((k = records[i].key) == key) {
              if (records[i - 1].ptr != (t = records[i].ptr) && t) {
                if (k == records[i].key) {
                  ret = t;
                  break;
                }
              }
            }
          }

          if (!ret) {
            if ((k = records[0].key) == key) {
              if (NULL != (t = records[0].ptr) && t) {
                if (k == records[0].key) {
                  ret = t;
                  continue;
                }
              }
            }
          }
        }
      } while (hdr.switch_counter != previous_switch_counter);

      if (ret) {
        return ret;
      }

      if ((t = (char*) hdr.sibling_ptr) && key >= ((Page*) t)->records[0].key)
        return t;

      return NULL;
    } else { // internal node
      do {
        previous_switch_counter = hdr.switch_counter;
        ret = NULL;

        if (IS_FORWARD(previous_switch_counter)) {
          if (key < (k = records[0].key)) {
            if ((t = (char*) hdr.leftmost_ptr) != records[0].ptr) {
              ret = t;
              continue;
            }
          }

          for (i = 1; records[i].ptr != NULL; ++i) {
            if (key < (k = records[i].key)) {
              if ((t = records[i - 1].ptr) != records[i].ptr) {
                ret = t;
                break;
              }
            }
          }

          if (!ret) {
            ret = records[i - 1].ptr;
            continue;
          }
        } else { // Search from right to left
          for (i = count() - 1; i >= 0; --i) {
            if (key >= (k = records[i].key)) {
              if (i == 0) {
                if ((char*) hdr.leftmost_ptr != (t = records[i].ptr)) {
                  ret = t;
                  break;
                }
              } else {
                if (records[i - 1].ptr != (t = records[i].ptr)) {
                  ret = t;
                  break;
                }
              }
            }
          }
        }
      } while (hdr.switch_counter != previous_switch_counter);

      if ((t = (char*) hdr.sibling_ptr) != NULL) {
        if (key >= ((Page*) t)->records[0].key)
          return t;
      }

      if (ret) {
        return ret;
      } else
        return (char*) hdr.leftmost_ptr;
    }
    return NULL;
  }

};


#endif //MOBILEDB_FF_BTREE_HH
