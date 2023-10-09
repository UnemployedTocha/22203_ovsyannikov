#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include "UnorderedList.h"

typedef std::string Key;
#define DEFAULT_SIZE_CAP 4 //


class HashTable{
public:
    HashTable();
    ~HashTable();
    HashTable(const HashTable& B);
    HashTable(HashTable&& B);

    void Swap(HashTable& b);
    HashTable& operator=(const HashTable& B);
    void clear();
    bool erase(const Key& k);
    bool insert(const Key& k, const Value& v);
    bool contains(const Key& k) const;
    Value& operator[](const Key& k);
    Value& at(const Key& k);
    const Value& at(const Key& k) const;
    size_t Size() const;
    bool empty() const;
    friend bool operator==(const HashTable& a, const HashTable& b);
    friend bool operator!=(const HashTable& a, const HashTable& b);
private:    
    List* _arr = nullptr;
    size_t _cap = 0;
    size_t _sz = 0;
    
    size_t Hash(std::string key);
    void Resize(size_t newSize);

};