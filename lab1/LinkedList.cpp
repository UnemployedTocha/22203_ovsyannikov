#include <string>
#include <iostream>

struct Value {
    unsigned age;
    unsigned weight;
};

struct ListNode{
    std::string key;
    Value data; 
    struct ListNode* pNext = nullptr;
};


class LinkedList{
public:
    LinkedList() = default;
    LinkedList(const std::string& incomingString){
        _pFirstNode = new ListNode;
        _pLastNode = _pFirstNode;
        _pFirstNode -> key = incomingString;    
    }
    LinkedList(const LinkedList& incomingList){
        _pFirstNode = new ListNode;
        _pLastNode = _pFirstNode;

        if(!IsEmpty(incomingList)){
            ListNode* pTemp = (incomingList._pFirstNode);
            while(pTemp != nullptr){
                CopyNode(pTemp);
                pTemp = (pTemp -> pNext);  
            }
        }

    }
    void Push(const LinkedList&){
        
    }
    void PrintNode(){
        std::cout << _pFirstNode -> key << std::endl;
    }
    ~LinkedList(){
    }   
private:
    ListNode* _pFirstNode = nullptr;
    ListNode* _pLastNode = nullptr;

    void CopyNode(ListNode* incomingNode){
        (_pFirstNode -> key) = (incomingNode -> key);
        (_pFirstNode -> data.age) = (incomingNode -> data.age);
        (_pFirstNode -> data.weight) = (incomingNode -> data.weight);
        (_pFirstNode -> pNext) = (incomingNode -> pNext);            
    }
    bool IsEmpty(const LinkedList& incomingList){
        if(nullptr == (incomingList._pFirstNode)){
            return true;
        }
        return false;
    }
    bool AreKeysEqual(const LinkedList& L1, const LinkedList& L2){
        if((L1._pFirstNode) -> key == (L2._pFirstNode) -> key){
            return true;
        }
        return false;
    }
};


int main(){
    LinkedList A("abcder");
    LinkedList B = A;
    B.PrintNode();
    return 0;
}   
