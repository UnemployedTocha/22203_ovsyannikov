#include "HashTable.h"
#include <algorithm>
#include <stdexcept>

HashTable::HashTable(): _cap(DEFAULT_SIZE_CAP), _sz(0), _arr(new List[_cap]) {}

HashTable::~HashTable() {
    delete[] _arr;

}

HashTable::HashTable(const HashTable& B): _cap(B._cap), _sz(B._sz), _arr(new List[_cap]) {
    std::copy(B._arr, B._arr + _cap, _arr);
}

HashTable::HashTable(HashTable&& B) noexcept : _cap(B._cap), _sz(B._sz), _arr(B._arr) {
    B._arr = nullptr;
}

void HashTable::Swap(HashTable& B) {
    std::swap(_arr, B._arr);
    std::swap(_cap, B._cap);
    std::swap(_sz, B._sz);
}

HashTable& HashTable::operator=(const HashTable& B) {
    if(this == &B) {
        return *this;
    }
    HashTable A = B;
    Swap(A);
    return *this;
}

void HashTable::Clear() {
    delete[] _arr;
    _arr = new List[DEFAULT_SIZE_CAP];
    _cap = DEFAULT_SIZE_CAP;
    _sz = 0;
}

bool HashTable::Erase(const Key& key) {
    const size_t index = Hash(key);
    bool isErased = _arr[index].Erase(key);
    _sz = _sz - isErased;
    return isErased;
}

bool HashTable::Insert(const Key& key, const Value& data) {
    if(Contains(key)){
        return false;
    }

    if(_sz >= _cap) {
        Resize(_cap * 2);
    }
    const size_t index = Hash(key);
    _arr[index].Push(key, data);
    ++_sz;
    return true;
}

bool HashTable::Contains(const Key& key) const {
    return _arr[Hash(key)].Contains(key);
}

Value& HashTable::operator[](const Key& key) {
    const size_t index = Hash(key);
    _arr[index].ValueByKey(key);
    return _arr[index].ValueByKey(key);
}

Value& HashTable::At(const Key& key) {
    size_t index = Hash(key);
    if(Contains(key)){
        return _arr[index].ValueByKey(key);
    }
    throw std::runtime_error("No such element");
}

const Value& HashTable::At(const Key& key) const {
    size_t index = Hash(key);
    if(Contains(key)) {
        return _arr[index].ValueByKey(key);
    }
    throw std::runtime_error("No such element");
}

bool operator==(const HashTable& A, const HashTable& B) {
    if(A.Size() != B.Size()) {
        return false;
    }
    size_t size = A.Size();
    for(size_t i = 0; i < size; ++i) {
        List::Iterator it = A._arr[i].Begin();
        while(A._arr[i].End() != it) {
            bool isEqualNodeExist = false;
            if(B.Contains((*it))) {
                isEqualNodeExist = true;
            }
            if(!isEqualNodeExist) {
                return false;
            }
            ++it;
        }
    }
    return true;
}

bool operator!=(const HashTable& A, const HashTable& B) {
    return !(A == B);
}

size_t HashTable::Size() const {
    return _sz;
}
bool HashTable::Empty() const {
    return _sz == 0;
}

size_t HashTable::Hash(const Key& key) const {
    size_t hash = 0;
    for(char i : key) {
        hash += i;
        hash %= _cap;
    }
    return hash;
}

void HashTable::Resize(size_t newSize) {
    List* pTemp = _arr;
    size_t oldCapacity = _cap;

    _arr = new List[newSize];
    _cap = newSize;

    for(size_t i = 0; i < oldCapacity; ++i) {
        while(pTemp[i].Size() > 0) {
            size_t index = Hash(pTemp[i].TopNodeKey());
            _arr[index].MoveTopNode(pTemp[i]);
        }
    }
    delete[] pTemp;
}

