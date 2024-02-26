#include "UnorderedList.h"

typedef std::string Key;

Value::Value(): age(0), weight(0) {}

Value::Value(unsigned age, unsigned weight): age(age), weight(weight) {}

bool operator==(const Value& A, const Value& B){
    if((A.age == B.age) && (A.weight == B.weight)){
        return true;
    }
    return false;
}

List::List() : _sz(0), _pFirstNode(nullptr){}


List::~List() {
    FreeList();
}

void List::Push(const std::string& key,const Value& data) {
    ++_sz;

    ListNode* pTemp = _pFirstNode;
    _pFirstNode = NewNode(key, data);
    _pFirstNode -> pNext = pTemp;
}

void List::Push(List::ListNode& N) {
    ++_sz;

    List::ListNode* pTemp = _pFirstNode;
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

List::ListNode* List::Pop() {
    List::ListNode* pTemp = _pFirstNode;
    _pFirstNode = pTemp -> pNext;
    --_sz;
    return pTemp;

}

List& List::operator=(const List& L) {
    if(this == &L) {
        return *this;
    }

    FreeList();

    if(L.IsEmpty()) {
        _pFirstNode = nullptr;
        _sz = 0;
        return *this;
    }

    _sz = L._sz;

    CopyList(L);
    return *this;
}

void List::MoveTopNode(List& listFrom) {
    this -> Push(*(listFrom.Pop()));
    return;
}
const std::string& List::TopNodeKey() const{
    return _pFirstNode -> key;
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
        pTemp = pTemp -> pNext;
    }
    Value data;
    Push(key, data);
    return _pFirstNode -> data;
}

List::ListNode* List::NewNode(const std::string& key,const Value& data) {
    List::ListNode* newNode = new ListNode;
    newNode -> key = key;
    newNode -> data = data;
    return newNode;
}

void List::FillData(ListNode* pNodeTo, ListNode* pNodeFrom) {
    pNodeTo -> data = pNodeFrom -> data;
    pNodeTo -> key = pNodeFrom -> key;
}

void List::CopyList(const List& L) {
    if(nullptr != L._pFirstNode) {
        ListNode* pTemp = L._pFirstNode;

        ListNode* newNode = new ListNode;
        FillData(newNode, pTemp);
        _pFirstNode = newNode;

        pTemp = pTemp -> pNext;
        while(nullptr != pTemp) {
            ListNode* pPrevTemp = newNode;
            newNode = new ListNode;
            pPrevTemp -> pNext = newNode;

            FillData(newNode, pTemp);
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
List::Iterator List::Begin() const{
    Iterator it(_pFirstNode);
    return it;
}
List::Iterator List::End() const{
    Iterator it(nullptr);
    return it;
}

//List::Iterator::Iterator() : _pNode(nullptr) {};
List::Iterator::Iterator(ListNode* pNode) : _pNode(pNode) {}
List::Iterator& List::Iterator::operator++() {
    _pNode = _pNode -> pNext;
    return *this;
}
std::string& List::Iterator::operator*() {
    return _pNode -> key;
}

bool operator==(const List& A, const List& B) {
    auto itListA = A.Begin();
    while(itListA != A.End()) {
        auto itListB = B.Begin();
        bool isEqualNodeExist = false;

        while(itListB != B.End()) {
            if((*itListA) == (*itListB)){
                isEqualNodeExist = true;
            }
            ++itListB;
        }
        if(!isEqualNodeExist) {
            return false;
        }
        ++itListA;
    }
    return true;
}
bool operator!=(const List& A, const List& B) {
    return !(A == B);
}
bool operator==(const List::Iterator& A, const List::Iterator& B) {
    return A._pNode == B._pNode;
}
bool operator!=(const List::Iterator& A, const List::Iterator& B) {
    return !(A == B);
}


