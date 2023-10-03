#include <iostream>
#include <string>
#include "LinkedList.h"

class HashTable{
public:
    HashTable(){
        _arr = new List[1];
        _cap = 1;
    };
    ~HashTable(){
        delete[] _arr;    
    }

    HashTable(const HashTable& hashTab){


    }
    HashTable(const HashTable&& b);

    void Swap(HashTable& b);

    HashTable& operator=(const HashTable& b);

    void Clear();
    
    bool Errase(const Key& k);

    bool Insert(const Key& k, const Value& v);

    bool Contains(const Key& k) const;

    Value& operator[](const Key& k);

    Value& At(const Key& k);
    const Value& At(const Key& k) const;

    size_t Size() const{
        size_t sz = 0;
        for(size_t i = 0; i < _cap; ++i){
            if(false == _arr[i].IsListEmpty()){
                sz += _arr[i].Size();
            }   
        }
        return sz;
    }
    bool Empty() const{
        return (_sz > 0) ? false : true; 
    }

    friend bool operator==(const HashTable& a, const HashTable& b);
    friend bool operator!=(const HashTable& a, const HashTable& b);

private:
    size_t _sz = 0;
    size_t _cap = 0;
    List* _arr;

    size_t GetHash(std::string key){
        size_t hash = 0;
        for(size_t i = 0; i < key.size(); i++){
            hash += key[i];    
        }
        return hash % key.size(); 
    }
    void ResizeArr(size_t n){

    }


};



int main(){
    //HashTable A;
    //std::cout << getHash(str); 

    return 0;
}