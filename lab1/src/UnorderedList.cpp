#include "UnorderedList.h"

typedef std::string Key;

Value::Value() = default;
Value::Value(unsigned age, unsigned weight): age(age), weight(weight){}
Value& Value::operator=(const Value& data){
    age = data.age;
    weight = data.weight;
    return *this;
}
unsigned Value::GetAge() const{
    return age;
}
unsigned Value::GetWeight() const{
    return weight;
}    
List::List() = default;
List::List(const List& L): _sz(L._sz){
    ListNode* pTemp = L._pFirstNode;
    if(nullptr != L._pFirstNode){
        ListNode* newNode = new ListNode;
        FillNode(newNode, pTemp);
        _pFirstNode = newNode;

        pTemp = pTemp -> pNext;
        while(nullptr != pTemp){
            newNode = new ListNode;
            FillNode(newNode, pTemp);
            pTemp = pTemp -> pNext;
        }   
    }
}
List::List(List&& L): _pFirstNode(L._pFirstNode), _sz(L._sz){
    L._pFirstNode = nullptr;
    L._sz = 0;    
}
List::List(std::string key, Value data): _sz(1){
    ListNode* newNode = NewNode(key, data);
    _pFirstNode = newNode;  
}
List::~List(){
    FreeList(this);        
}

void List::Push(std::string key, Value data){
    ++_sz;

    ListNode* pTemp = _pFirstNode;
    _pFirstNode = NewNode(key, data);
    _pFirstNode -> pNext = pTemp;
}
void List::Push(ListNode& N){
    ++_sz;

    ListNode* pTemp = _pFirstNode;
    _pFirstNode = &N;
    N.pNext = pTemp;
}
bool List::Pop(std::string key){ // Returns the success of Pop(). 
    if(IsEmpty()){
        return false;
    } 

    ListNode* pTemp = _pFirstNode -> pNext;
    if(_pFirstNode->key == key){
        delete _pFirstNode;
        _pFirstNode = pTemp;
        --_sz;
        return true;
    }

    ListNode* pPrevTemp = _pFirstNode;
    while(nullptr != pTemp){
        if(pTemp->key == key){
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
ListNode* List::Pop(){ // Returns top node/nullptr if pop is unsuccessful 
    if(IsEmpty()){
        return nullptr;
    } 
    ListNode* pTemp = _pFirstNode;
    _pFirstNode = pTemp -> pNext;
    --_sz;
    return pTemp;

}
List& List::operator=(const List& L){
    if(this == &L){
        return *this;
    }
    FreeList(this);
    _sz = L._sz;

    ListNode* pTemp = L._pFirstNode;
    if(nullptr != L._pFirstNode){
        ListNode* newNode = new ListNode;
        FillNode(newNode, pTemp);
        _pFirstNode = newNode;

        pTemp = pTemp -> pNext;
        while(nullptr != pTemp){
            newNode = new ListNode;
            FillNode(newNode, pTemp);
            pTemp = pTemp -> pNext;
        }   
    }
    return *this;
}
List& List::operator=(List&& L){
    if(this == &L){
        return *this;
    }
    FreeList(this);
    _pFirstNode = L._pFirstNode;
    _sz = L._sz;

    L._pFirstNode = nullptr;
    L._sz = 0;
    return *this;
}
bool List::IsEmpty() const{
    return (_sz == 0) ? true : false;
}

void List::PrintList() const{
    ListNode* pTemp = _pFirstNode;
    while(nullptr != pTemp){
        std::cout << pTemp -> key << ((pTemp -> data).GetAge()) << ((pTemp -> data).GetWeight()) << std::endl;
        pTemp = pTemp -> pNext;
    }
}   

ListNode* List::NewNode(std::string key, Value data){
    ListNode* newNode = new ListNode;
    newNode -> key = key;
    (newNode -> data) = data;
    return newNode;  
}
void List::FillNode(ListNode* pNodeTo, ListNode* pNodeFrom){
    pNodeTo -> data = pNodeFrom -> data;
    pNodeTo -> key = pNodeFrom -> key;
    pNodeTo -> pNext = pNodeFrom -> pNext;
}

void List::FreeList(List* pList){
    ListNode* pTemp = pList->_pFirstNode;
    while(nullptr != pTemp){
        ListNode* pNextNode = pTemp -> pNext;
        delete pTemp;
        pTemp = pNextNode;
    }
}
size_t List::Size() const{
    return _sz;
}
bool operator==(const List& L1, const List& L2){
    if(L1.IsEmpty() && L2.IsEmpty()){
        return true;
    }
    if(L1.Size() != L2.Size()){
        return false;
    }

    ListNode* p1 = L1._pFirstNode;
    ListNode* p2 = L2._pFirstNode;
    for(size_t i = 0; i < L1.Size(); ++i){
        bool isEqualNodeExist = false;
        for(size_t j = 0; i < L2.Size(); ++j){
            if((p1 -> key) == (p2 -> key)){
                isEqualNodeExist = true;
                break;
            }
            p2 = p2 -> pNext;
        }
        if(false == isEqualNodeExist){
            return false;
        }
        p1 = p1 -> pNext;
        p2 = L2._pFirstNode;
    }
    return true;
}