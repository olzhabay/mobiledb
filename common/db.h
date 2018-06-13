#ifndef MOBILEDB_DB_H
#define MOBILEDB_DB_H

class DB {
    DB() = default;

    DB(const DB&) = delete;
    DB& operator=(const DB&) = delete;
    virtual ~DB();

    virtual Status Put(const Slice& key, const Slice& value) = 0;
    virtual Status Get(const Slice& key, std::string* value) = 0;
    virtual Status Delete(const Slice& key) = 0;
};

#endif //MOBILEDB_DB_H
