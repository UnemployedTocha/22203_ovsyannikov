#include "HashTable.h"

HashTable::HashTable(): _arr(new List[DEFAULT_SIZE_CAP]), _cap(DEFAULT_SIZE_CAP), _sz(0){}
HashTable::~HashTable(){
    delete[] _arr;
}
HashTable::HashTable(const HashTable& B): _cap(B._cap), _sz(B._sz), _arr(new List[_cap]){
    for(size_t i = 0; i < _cap; ++i){
        _arr[i] = B._arr[i];
    }
}
HashTable::HashTable(HashTable&& B): _arr(B._arr), _cap(B._cap), _sz(B._sz){
    B._arr = new List[DEFAULT_SIZE_CAP];
    B._cap = DEFAULT_SIZE_CAP;
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
    HashTable A = B;
    Swap(A);
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
void HashTable::Clear(){
    delete[] _arr;
    _arr = new List[DEFAULT_SIZE_CAP];
    _cap = DEFAULT_SIZE_CAP;
    _sz = 0;

}
bool HashTable::Erase(const Key& key){
    size_t index = Hash(key);
    bool isErased;
    isErased = _arr[index].Pop(key);
    return isErased;
}
bool HashTable::Insert(const Key& key, const Value& data){
    if(_sz >= _cap){
        bool flag = Resize(_cap * 2);
        if(!flag){
            return false;
        }
    }
    size_t index = Hash(key);
    _arr[index].Push(key, data);
    return true;
}
bool HashTable::Contains(const Key& key) const{
    size_t index = Hash(key);
    if(_arr[index].Contains(key)){
        return true;
    }
    return false;
}
Value& HashTable::operator[](const Key& key){
    size_t index = Hash(key);
    if(Contains(key)){
        return _arr[index].ValueByKey(key);     
    }
    Value data;
    _arr[index].Push(key, data);
    return _arr[index].ValueByKey(key);
}
Value& HashTable::At(const Key& key){
    size_t index = Hash(key);
    if(Contains(key)){
        return _arr[index].ValueByKey(key);     
    }
    throw "No such element with such key";  
}
const Value& HashTable::At(const Key& key) const{
    size_t index = Hash(key);
    if(Contains(key)){
        return _arr[index].ValueByKey(key);     
    }
    throw "No such element with such key";  
}
bool operator==(const HashTable& A, const HashTable& B){
    if(A.Size() != B.Size()){
        return false;
    }        
    size_t size = A.Size();
    for(size_t i = 0; i < size; ++i){
        ListNode* pNodeA = (A._arr[i]).GetFirstNodePointer();
        while(nullptr != pNodeA){
            bool isEqualNodeExist = false;
            for(size_t j = 0; j < size; ++j){
                ListNode* pNodeB = (B._arr[j]).GetFirstNodePointer();
                while(nullptr != pNodeB){
                    if(pNodeA -> key == pNodeB -> key){
                        isEqualNodeExist = true;
                        break;
                    }
                    pNodeB = pNodeB -> pNext;
                }            
            }
            if(false == isEqualNodeExist){
                return false;
            }
            pNodeA = pNodeA -> pNext;
        }
    }
    return true;
}
bool operator!=(const HashTable& A, const HashTable& B){
    return !(A == B);
}
size_t HashTable::Size() const{
    return _sz;
}
size_t HashTable::Hash(const Key& key) const{
    size_t hash = 0;
    for(size_t i = 0; i < _cap; ++i){
        hash += key[i];
        hash %= _cap;
    }
    return hash;
}
bool HashTable::Resize(size_t newSize){
    if(newSize < _cap){
        return false;
    }    
    List* pTemp = _arr;
    
    try {
        _arr = new List[newSize];
    }catch(...){
        return false;
    }
    for(size_t i = 0; i < _cap; ++i){
        while(pTemp[i].Size() > 0){
            ListNode* node = pTemp[i].Pop();      
            int index = Hash(node -> key);
            _arr[index].Push(*node);  
        }
    }
    delete pTemp;
    _cap = newSize;
    return true;    
}
// bool HashTable::Insert(const std::string& key, const Value& data, size_t index){
//     if(_cap <= _sz + 1){
//         resize(_cap * 2);
//     }
    
// }

