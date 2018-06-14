#ifndef MOBILEDB_STORE_MANAGER_HH
#define MOBILEDB_STORE_MANAGER_HH

#include "../common/persist.hh"
#include "../common/slice.hh"

class StorageManager {
public:

  static void* Store(const Slice& data);
  static Slice Get(void* ptr);
  static void Erase(void* ptr);
private:
  struct DataValue {
    size_t size;
    char* ptr;
  };
};


#endif //MOBILEDB_STORE_MANAGER_HH
