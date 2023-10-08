#include "HashTable.h"

// HashTable::Array::Array(): _arr(new List[DEFAULT_SIZE_CAP]), _cap(DEFAULT_SIZE_CAP){}
// HashTable::Array(const Array& A): _cap(A._cap), _sz(A._sz){
//     _arr = new List[_cap];
//     for(size_t i = 0; i < _cap; ++i){
//         _arr[i] = A._arr[i];
//     }
// }
// HashTable::Array(Array&& A): _arr(A._arr), _cap(A._cap), _sz(A._sz){
//     A._arr = nullptr;
//     A._cap = 0;
//     A._sz = 0;
// }
// HashTable::Array(const std::string& key, const Value data, size_t index): _sz(1), _cap(DEFAULT_SIZE_CAP){
//     _arr = new List[DEFAULT_SIZE_CAP];
//     _arr[index].Push(key, data);
// }
// Array& HashTable::operator=(const Array& A){
//     if(this == &A){
//         return *this;
//     }
//     delete[] _arr;
//     List* _arr = new List[A._cap];
//     for(size_t i = 0; i < A._cap; ++i){
//         _arr[i] = A._arr[i];
//     }
//     return *this;
// }
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
// void HashTable::Resize(size_t newSize){
//     if(newSize <= _cap){
//         return;
//     }    
//     List* tempArr = std::move(_arr);
//     _arr = new List[newSize];
//     for(size_t i = 0; i < _cap; ++i){
//         _arr[i] = std::move(tempArr[i]);
//     }
//     _cap = newSize;    
// }
// size_t HashTable::Size() const{
//     return _sz;
// }
// size_t Capacity() const{
//     return _cap;
// }
// bool HashTable::Insert(const std::string& key, const Value& data, size_t index){
//     if(_cap <= _sz + 1){
//         resize(_cap * 2);
//     }
    
// }

