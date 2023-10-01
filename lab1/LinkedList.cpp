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


class List{
public:
    List() = default;
    List(const std::string& inputString){
        ListNode* newNode = NewNode(inputString);    
        _pFirstNode = newNode;
    }
    List(const List& inputList){
        if(!IsListEmpty(inputList)){
            ListNode* newNode = new ListNode;
            newNode = CopyNode(*(inputList._pFirstNode));
            _pFirstNode = newNode;

            ListNode* pTemp = (inputList._pFirstNode) -> pNext;
            while(pTemp != nullptr){
                newNode = new ListNode;
            }
        }
    }


    void PrintNode(){
        std::cout << _pFirstNode -> key << std::endl;
    }
    ~List(){
        }   
private:
    ListNode* _pFirstNode = nullptr;

    void CopyNode(ListNode* nodeTo, const ListNode& nodeFrom){
        (nodeTo -> data).age = (nodeFrom.data).age;
        (nodeTo -> data).weight = (nodeFrom.data).weight;
        nodeTo -> key = nodeFrom.key;
        nodeTo -> pNext = nodeFrom.pNext;
    }
    ListNode* NewNode(const ListNode& node){
        ListNode* newNode = new ListNode;
        CopyNode(NewNode, node);
        return newNode;
    }
    ListNode* NewNode(const std::string str){
        ListNode* newNode = new ListNode;
        newNode -> key = str;
        return newNode;

    }

    bool IsListEmpty(const List& inputList){
        if(nullptr == (inputList._pFirstNode)){
            return true;
        }
        return false;
    }
    bool AreKeysEqual(const List& L1, const List& L2){
        return (L1._pFirstNode -> key == (L2._pFirstNode) -> key) ? true : false; 
    }
};


int main(){
    List A("abcder");
    List B = A;
    B.PrintNode();
    return 0;
}   
