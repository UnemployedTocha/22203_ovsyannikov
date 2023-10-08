#pragma once

#include <iostream>
#include <string>

struct Value {
    unsigned age;
    unsigned weight;
};

struct ListNode{
    std::string key;
    Value data; 
    struct ListNode* pNext = nullptr;
};
void FillValue(Value& p, int age, int weight);


class List{    
public:
    List();
    List(std::string key, Value data);
    List(const List& L);
    List(List&& L);
    List& operator=(const List& L);
    List& operator=(List&& L);
    friend bool operator==(const List& L1, const List& L2); 
    ~List();
    void Push(std::string key, Value data);
    bool Pop(std::string key);
    bool IsEmpty() const;
    void PrintList() const;
    size_t Size() const;
private:
    ListNode* _pFirstNode = nullptr;
    size_t _sz = 0;

    ListNode* NewNode(std::string key, Value data);
    void FillNode(ListNode* pNodeFrom, ListNode* pNodeTo);
    void FreeList(List* pList);
};