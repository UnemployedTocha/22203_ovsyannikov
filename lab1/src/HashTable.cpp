#include "HashTable.h"

HashTable::HashTable(): _arr(new List[DEFAULT_SIZE_CAP]), _cap(DEFAULT_SIZE_CAP){}
HashTable::~HashTable(){
    delete[] _arr;
}
HashTable::HashTable(const HashTable& B): _cap(B._cap), _sz(B._sz){
    _arr = new List[_cap];
    for(size_t i = 0; i < _cap; ++i){
        _arr[i] = B._arr[i];
    }
}
HashTable::HashTable(HashTable&& B): _arr(B._arr), _cap(B._cap), _sz(B._sz){
    B._arr = nullptr;
    B._cap = 0;
    B._sz = 0;
}
void HashTable::Swap(HashTable& B){
    std::swap(_arr, B._arr);
    std::swap(_cap, B._cap);
    std::swap(_sz, B._sz);
}
// HashTable::HashTable(const std::string& key, const Value data, size_t index): _sz(1), _cap(DEFAULT_SIZE_CAP){
//     _arr = new List[DEFAULT_SIZE_CAP];
//     _arr[index].Push(key, data);
// }
HashTable& HashTable::operator=(const HashTable& B){
    if(this == &B){
        return *this;
    }
    delete[] _arr;
    List* _arr = new List[B._cap];
    for(size_t i = 0; i < A._cap; ++i){
        _arr[i] = A._arr[i];
    }
    return *this;
}
// Array& HashTable::operator=(Array&& A){
//     if(this == &A){
//         return *this;
//     }
//     delete[] _arr;
//     List* _arr = A._arr;
//     _cap = A._cap;
//     _sz = A._sz;

//     A._cap = 0;
//     A._sz = 0;
//     A._arr = nullptr;
//     return *this;
// }
size_t HashTable::Size() const{
    return _sz;
}
size_t HashTable::Hash(std::string key){
    size_t hash = 0;
    for(size_t i = 0; i < _cap; ++i){
        hash += key[i];
        hash %= _cap;
    }
    return hash;
}
void HashTable::Resize(size_t newSize){
    if(newSize <= _cap){
        return;
    }    
    List* pTemp = _arr;
    _arr = new List[newSize];
    for(size_t i = 0; i < _cap; ++i){
        while(pTemp[i].Size() > 0){
            ListNode* node = pTemp[i].Pop();      
            int index = Hash(node -> key);
            _arr[index].Push(*node);  
        }
    }
    delete pTemp;
    _cap = newSize;    
}
// bool HashTable::Insert(const std::string& key, const Value& data, size_t index){
//     if(_cap <= _sz + 1){
//         resize(_cap * 2);
//     }
    
// }

