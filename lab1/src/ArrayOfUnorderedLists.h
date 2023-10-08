#pragma once
#include <iostream>
#include <string>
#include "UnorderedList.h"

#define DEFAULT_SIZE_CAP 4

class Array{
public:
    Array();
    Array(const std::string& key, const Value data, size_t index);
    Array(const Array& A);
    Array(Array&& A);
    Array& operator=(const Array& A);
    Array& operator=(Array&& A);

    size_t Size() const;
    void Resize(size_t newSize);
    size_t Capacity() const;
    void IsEmpty() const;
    bool Insert(const std::string& key, const Value& data, size_t index);
private:
    List* _arr = nullptr;
    size_t _cap = 0;
    size_t _sz = 0;
};
