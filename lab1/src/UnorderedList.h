#pragma once

#include <iostream>
#include <string>

class Value {
public:
    Value();    
    Value(unsigned age, unsigned weight);
    Value& operator=(const Value& data);
    unsigned GetAge() const;
    unsigned GetWeight() const;
private:
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
    List();
    List(std::string key, Value data);
    List(const List& L);
    List(List&& L);
    List& operator=(const List& L);
    List& operator=(List&& L);
    friend bool operator==(const List& L1, const List& L2); 
    ~List();
    void Push(std::string key, Value data);
    void Push(ListNode& N);
    bool Pop(std::string key);
    ListNode* Pop();
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