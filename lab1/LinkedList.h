#ifndef LINKEDLIST_H
#define LINKEDLIST_H

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
    List(const std::string& key, Value data);
    List(const List& inputList);
    void PushNode(ListNode& Node);
    bool IsNodeExist(std::string key);
    void pop(std::string key);
    List& operator=(const List& L);
    size_t Size() const;
    bool IsListEmpty();
    bool IsListEmpty(const List& inputList);
    void PrintList();
    ~List();
    void PrintKey();
private:
    ListNode* _pFirstNode = nullptr;
    size_t _sz = 0;

    void CopyNode(ListNode* nodeTo,const ListNode& nodeFrom);
    ListNode* NewNode(const ListNode& node);
    ListNode* NewNode(const std::string str, Value data);
    bool AreKeysEqual(const List& L1, const List& L2);
    void FreeList();
};

#endif