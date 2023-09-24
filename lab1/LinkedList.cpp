#include <string>
#include <iostream>

struct Value {
    unsigned age;
    unsigned weight;
};

struct ListNode{
    std::string key;
    Value data; 
    struct ListNode* pNext;
};


class LinkedList{
public:
    LinkedList() = default;
    LinkedList(const std::string& incomingString){
        _pFirstNode = new ListNode;
        _pLastNode = _pFirstNode;
        (_pFirstNode -> key) = incomingString;
    }
    LinkedList(const LinkedList& incomingList){

    }
    void Push(std::string S){

    }
    void PrintNode(){
        std::cout << _pFirstNode -> key << std::endl;
    }
    ~LinkedList(){
    }   
private:
    ListNode* _pFirstNode = nullptr;
    ListNode* _pLastNode = nullptr;
};


int main(){
    LinkedList A("abcdr");
    A.PrintNode();
    return 0;
}   
