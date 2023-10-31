#pragma once

#include <string>

class Value {
public:
    Value();    
    Value(unsigned age, unsigned weight);
    Value& operator=(const Value& data);
    friend bool operator==(const Value& A, const Value& B);
    unsigned GetAge() const;
    unsigned GetWeight() const;
private:
    unsigned age;
    unsigned weight;
};


class List{    
public:


    List();
    List(const std::string& key,const Value& data);
    List(const List& L);
    List(List&& L);
    List& operator=(const List& L);
    List& operator=(List&& L);
    ~List();
    void Push(const std::string& key,const Value& data);
    bool Erase(const std::string& key);
    bool Contains(const std::string& key) const;
    Value& ValueByKey(const std::string& key); 


    
    Iterator::Iterator Begin(){
        Iterator it(_pFirstNode);
        return it;    
    }
    Iterator::Iterator End(){
        Iterator it(nullptr);
        return it;
    }
    
    bool IsEmpty() const;
    void PrintList() const;
    size_t Size() const;

private:
    ListNode* _pFirstNode = nullptr;
    size_t _sz = 0;


    struct ListNode {
        std::string key;
        Value data; 
        struct ListNode* pNext = nullptr;
    };

    ListNode* NewNode(const std::string& key,const Value& data);
    void FillNode(ListNode* pNodeFrom, ListNode* pNodeTo);
    void CopyList(const List& L);
    void FreeList();

    void Push(ListNode& N);
    ListNode* Pop();
    // ListNode* GetFirstNodePointer() const;



};