#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include "UnorderedList.h"

typedef std::string Key;
#define DEFAULT_SIZE_CAP 2


class HashTable{
public:
    HashTable();
    ~HashTable();
    HashTable(const HashTable& B);
    HashTable(HashTable&& B);

    void Swap(HashTable& b);
    HashTable& operator=(const HashTable& B);
    void Clear();
    bool Erase(const Key& key);
    bool Insert(const Key& key, const Value& data);
    bool Contains(const Key& key) const;
    Value& operator[](const Key& key);
    Value& At(const Key& key);
    const Value& At(const Key& key) const;
    size_t Size() const;
    bool Empty() const;
    friend bool operator==(const HashTable& A, const HashTable& B);
    friend bool operator!=(const HashTable& A, const HashTable& B);
    void PrintHashTable() const;
private:    
    size_t _cap = DEFAULT_SIZE_CAP;
    size_t _sz = 0;
    List* _arr = nullptr;

    size_t Hash(const Key& key) const;
    bool Resize(size_t newSize);

};