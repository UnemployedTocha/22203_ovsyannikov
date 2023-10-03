#include <iostream>
#include <string>

typedef std::string Key;

struct Value {
    unsigned age;
    unsigned weight;
};

struct ListNode{
    std::string key;
    Value data; 
    struct ListNode* pNext = nullptr;
    struct ListNode* pPrev = nullptr;
};
void FillNode(ListNode& node, std::string key, unsigned age, unsigned weight){
    node.data.age = age;
    node.data.weight = weight;
    node.key = key;
}

class List{
public:
    List() = default;
    List(const std::string& key, Value data){
        ListNode* newNode = NewNode(key, data);    
        _pFirstNode = newNode;
        _sz = 1;
    }
    List(const List& inputList){
        if(!IsListEmpty(inputList)){
            ListNode* newNode = new ListNode;
            CopyNode(newNode, *(inputList._pFirstNode));
            _pFirstNode = newNode;
            _sz = inputList._sz;


            ListNode* pTemp = (inputList._pFirstNode) -> pNext;
            while(pTemp != nullptr){
                newNode = NewNode(*pTemp);
                pTemp = pTemp -> pNext;
            }
        }
        else{
            ListNode* newNode = new ListNode;    
            _pFirstNode = newNode;
            _sz = 1;    
        }
    }
    void PushNode(ListNode& Node){
            if(nullptr != _pFirstNode){
                ListNode* newNode = NewNode(Node);    

                ListNode* pTemp = _pFirstNode;
                _pFirstNode = newNode;
                newNode -> pNext = pTemp;
                pTemp -> pPrev = newNode;
                ++_sz;
            }
            else{
                ListNode* newNode = NewNode(Node);    
                _pFirstNode = newNode;
                ++_sz;
            }
    }
    bool IsNodeExist(std::string key){
        ListNode* pTemp = _pFirstNode;

        while(nullptr != pTemp){
            if(pTemp->key == key){
                return true;
            }
            return false;
        }
    }
    void pop(std::string key){
        if(nullptr != _pFirstNode){
            ListNode* pTemp = _pFirstNode -> pNext;

            if(_pFirstNode->key == key){
                if(nullptr != _pFirstNode -> pNext){
                    delete _pFirstNode;
                    _pFirstNode = pTemp;
                    --_sz;
                    std::cout << " AAA ";
                }
                else{
                    _sz = 0;
                    delete _pFirstNode;
                    _pFirstNode = nullptr;
                }
            }
            
            while(nullptr != pTemp){
                if(pTemp->key == key){
                    ListNode* pPrevTemp = pTemp -> pPrev;
                    ListNode* pNextTemp = pTemp -> pNext;
                    delete pTemp;
                    if(nullptr != pPrevTemp){
                        pPrevTemp -> pNext = pNextTemp;
                    }
                    if(nullptr != pNextTemp){
                        pNextTemp -> pPrev = pPrevTemp;
                    }
                    --_sz;
                    return;
                }
                pTemp = pTemp -> pNext;
            }    
        }
    }
    List& operator=(const List& L){
        if(&L == this){
            return *this;
        }
        FreeList();

        if(!IsListEmpty(L)){
            ListNode* newNode = new ListNode;
            CopyNode(newNode, *(L._pFirstNode));
            _pFirstNode = newNode;
            _sz = L._sz;


            ListNode* pTemp = (L._pFirstNode) -> pNext;
            while(pTemp != nullptr){
                newNode = NewNode(*pTemp);
                pTemp = pTemp -> pNext;
            }
            return *this;
        }
        else{
            ListNode* newNode = new ListNode;    
            _pFirstNode = newNode;
            _sz = 1;
            return *this;    
        }
        

    }
    size_t Size() const{
        return _sz;
    }
    bool IsListEmpty(){
        if(nullptr == _pFirstNode){
            return true;
        }
        return false;
    }
    bool IsListEmpty(const List& inputList){
        if(nullptr == (inputList._pFirstNode)){
            return true;
        }
        return false;
    }
    void PrintList(){
        ListNode* pTemp = _pFirstNode;
        while(pTemp != nullptr){
            std::cout << pTemp -> key << " " << std::endl;
            pTemp = pTemp -> pNext;
        }
    }
    ~List(){
        FreeList();     
    }   
    void PrintKey(){
        std::cout << _pFirstNode -> key << std::endl;
    }
private:
    ListNode* _pFirstNode = nullptr;
    size_t _sz = 0;

    void CopyNode(ListNode* nodeTo,const ListNode& nodeFrom){
        (nodeTo -> data).age = (nodeFrom.data).age;
        (nodeTo -> data).weight = (nodeFrom.data).weight;
        nodeTo -> key = nodeFrom.key;
        nodeTo -> pNext = nodeFrom.pNext;
        nodeTo -> pPrev = nodeFrom.pPrev;
    }
    ListNode* NewNode(const ListNode& node){
        ListNode* newNode = new ListNode;
        CopyNode(newNode, node);
        return newNode;
    }
    ListNode* NewNode(const std::string str, Value data){
        ListNode* newNode = new ListNode;
        newNode -> key = str;
        newNode -> data.age = data.age;
        newNode -> data.weight = data.weight;
        return newNode;
    }
    bool AreKeysEqual(const List& L1, const List& L2){
        return (L1._pFirstNode -> key == (L2._pFirstNode) -> key) ? true : false; 
    }
    void FreeList(){
        ListNode* pTemp = _pFirstNode;
        while(nullptr != pTemp){
            ListNode* pTempNext = pTemp -> pNext;
            delete pTemp;
            pTemp = pTempNext;
        }
    }
};
int main(){
    List A;

    ListNode N1, N2, N3;
    FillNode(N1, "1234", 12, 150);
    FillNode(N2, "Qwerty", 18, 175);
    FillNode(N3, "mmmm", 18, 175);

    A.PushNode(N1);
    A.PushNode(N2);

    List B;
    B = A;
    //std::cout << B.Size() << std::endl;
    B.PrintList();
    return 0;
}   
