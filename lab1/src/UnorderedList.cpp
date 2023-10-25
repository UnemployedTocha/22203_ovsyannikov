#include "UnorderedList.h"
#include <iostream>

typedef std::string Key;

Value::Value(): age(0), weight(0) {}

Value::Value(unsigned age, unsigned weight): age(age), weight(weight) {}

Value& Value::operator=(const Value& data) {
    age = data.age;
    weight = data.weight;
    return *this;
}

bool operator==(const Value& A, const Value& B) {
    if((A.age == B.age) && (A.weight == B.weight)){
        return true;
    }
    return false;
}

unsigned Value::GetAge() const {
    return age;
}

unsigned Value::GetWeight() const {
    return weight;
}

List::List() = default;

List::List(const List& L): _sz(L._sz) {
    if(L.IsEmpty()) {
        _pFirstNode = nullptr;
    }
    CopyList(L);
    
}

List::List(List&& L): _pFirstNode(L._pFirstNode), _sz(L._sz) {
    L._pFirstNode = nullptr;
    L._sz = 0;    
}

List::List(const std::string& key,const Value& data): _sz(1) {
    ListNode* newNode = NewNode(key, data);
    _pFirstNode = newNode;  
}

List::~List() {
    FreeList();        
}

void List::Push(const std::string& key,const Value& data) {
    ++_sz;

    ListNode* pTemp = _pFirstNode;
    _pFirstNode = NewNode(key, data);
    _pFirstNode -> pNext = pTemp;
}

void List::Push(ListNode& N) {
    ++_sz;

    ListNode* pTemp = _pFirstNode;
    _pFirstNode = &N;
    N.pNext = pTemp;
}

bool List::Erase(const std::string& key) {
    if(IsEmpty()) {
        return false;
    } 

    ListNode* pTemp = _pFirstNode -> pNext;
    if(_pFirstNode->key == key) {
        delete _pFirstNode;
        _pFirstNode = pTemp;
        --_sz;
        return true;
    }

    ListNode* pPrevTemp = _pFirstNode;
    while(nullptr != pTemp) {
        if(pTemp->key == key) {
            pPrevTemp -> pNext = pTemp -> pNext;
            delete pTemp;
            --_sz;
            return true;
        }
        pPrevTemp = pTemp;
        pTemp = pTemp -> pNext;
    }
    return false;
}

ListNode* List::Pop() { // Returns top node/nullptr if pop is unsuccessful 
    if(IsEmpty()) {
        return nullptr;
    } 
    ListNode* pTemp = _pFirstNode;
    _pFirstNode = pTemp -> pNext;
    --_sz;
    return pTemp;

}

List& List::operator=(const List& L) {
    if(this == &L) {
        return *this;
    }

    if(L.IsEmpty()) {
        _pFirstNode = nullptr;
        _sz = 0;
        return *this;       
    }

    FreeList();
    _sz = L._sz;

    CopyList(L);
    return *this;
}

List& List::operator=(List&& L) {
    if(this == &L) {
        return *this;
    }
    FreeList();
    _pFirstNode = L._pFirstNode;
    _sz = L._sz;

    L._pFirstNode = nullptr;
    L._sz = 0;
    return *this;
}

bool List::IsEmpty() const {
    return _sz == 0;
}

bool List::Contains(const std::string& key) const {
    ListNode* pTemp = _pFirstNode;
    while(nullptr != pTemp) {
        if(pTemp -> key == key) {
            return true;
        }
        pTemp = pTemp -> pNext;    
    }
    return false;
}

Value& List::ValueByKey(const std::string& key) {
    ListNode* pTemp = _pFirstNode;
    while(nullptr != pTemp) {
        if(pTemp -> key == key) {
            return pTemp -> data;
        }    
    }
    Value data;
    Push(key, data);
    return _pFirstNode -> data;
}

void List::PrintList() const {
    ListNode* pTemp = _pFirstNode;
    while(nullptr != pTemp) {
        std::cout << pTemp -> key << " " << ((pTemp -> data).GetAge()) << " " << ((pTemp -> data).GetWeight()) << std::endl;
        pTemp = pTemp -> pNext;
    }
}   

ListNode* List::NewNode(const std::string& key,const Value& data) {
    ListNode* newNode = new ListNode;
    newNode -> key = key;
    newNode -> data = data;
    return newNode;  
}

void List::FillNode(ListNode* pNodeTo, ListNode* pNodeFrom) {
    pNodeTo -> data = pNodeFrom -> data;
    pNodeTo -> key = pNodeFrom -> key;
    pNodeTo -> pNext = pNodeFrom -> pNext;
}

void List::CopyList(const List& L) {
    ListNode* pTemp = L._pFirstNode;
    if(nullptr != L._pFirstNode) {
        ListNode* newNode = new ListNode;
        FillNode(newNode, pTemp);
        _pFirstNode = newNode;

        pTemp = pTemp -> pNext;
        while(nullptr != pTemp) {
            newNode = new ListNode;
            FillNode(newNode, pTemp);
            pTemp = pTemp -> pNext;
        }   
    }    
}

void List::FreeList() {
    ListNode* pTemp = this -> _pFirstNode;
    while(nullptr != pTemp) {
        ListNode* pNextNode = pTemp -> pNext;
        delete pTemp;
        pTemp = pNextNode;
    }
}

size_t List::Size() const {
    return _sz;
}

ListNode* List::GetFirstNodePointer() const {
    return _pFirstNode;
}

