#pragma once

#include <string>

class Value {
private:
public:
    Value();
    Value(unsigned age, unsigned weight);
    friend bool operator==(const Value& A, const Value& B);
private:
    unsigned age;
    unsigned weight;
};

class List{
private:
    struct ListNode {
        std::string key;
        Value data;
        struct ListNode* pNext = nullptr;
    };
public:
    class Iterator;

    List();
    List& operator=(const List& L);
    ~List();
    void Push(const std::string& key,const Value& data);
    bool Erase(const std::string& key);
    bool Contains(const std::string& key) const;
    friend bool operator==(const List& A, const List& B);
    friend bool operator!=(const List& A, const List& B);
    void MoveTopNode(List& listFrom);
    const ListNode& Top() const;
    Value& ValueByKey(const std::string& key);

    bool IsEmpty() const;
    size_t Size() const;

    Iterator Begin() const;
    Iterator End() const;

    class Iterator {
    public:
        Iterator();

        Iterator(ListNode* pNode);

        Iterator& operator++();

        ListNode& operator*();

        friend bool operator==(const List::Iterator& A, const List::Iterator& B);

        friend bool operator!=(const List::Iterator& A, const List::Iterator& B);
    private:
        ListNode* _pNode;
    };
private:
    ListNode* _pFirstNode;
    size_t _sz;


    ListNode* NewNode(const std::string& key,const Value& data);
    void FillData(ListNode* pNodeFrom, ListNode* pNodeTo);
    void CopyList(const List& L);
    void FreeList();

    void Push(ListNode& N);
    ListNode* Pop();

};