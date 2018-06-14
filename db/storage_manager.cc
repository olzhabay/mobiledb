#include "storage_manager.hh"

void* StorageManager::Store(const Slice& data) {
  DataValue* data_value = new DataValue;
  data_value->size = data.size();
  data_value->ptr = new char[data_value->size];
  memcpy(data_value->ptr, data.data(), data_value->size);
  clflush(data_value->ptr, data_value->size);
  clflush((char*) data_value, sizeof(data_value));
  return data_value;
}

Slice StorageManager::Get(void* ptr) {
  DataValue* data_value = reinterpret_cast<DataValue*>(ptr);
  return Slice(data_value->ptr, data_value->size);
}

void StorageManager::Erase(void* ptr) {
  DataValue* data_value = reinterpret_cast<DataValue*>(ptr);
  delete data_value->ptr;
  delete data_value;
}

