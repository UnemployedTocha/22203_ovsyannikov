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

    ListNode* _pFirstNode;
    size_t _sz;


    ListNode* NewNode(const std::string& key,const Value& data);
    void FillData(ListNode* pNodeFrom, ListNode* pNodeTo);
    void CopyList(const List& L);
    void FreeList();

    void Push(ListNode& N);
    ListNode* Pop();

public:
    class Iterator;

    List();
    List& operator=(const List& L);
    ~List();
    void Push(const std::string& key,const Value& data);
    bool Erase(const std::string& key);
    [[nodiscard]] bool Contains(const std::string& key) const;
    friend bool operator==(const List& A, const List& B);
    friend bool operator!=(const List& A, const List& B);
    void MoveTopNode(List& listFrom);
    [[nodiscard]] const std::string& TopNodeKey() const;
    Value& ValueByKey(const std::string& key);

    [[nodiscard]] bool IsEmpty() const;
    [[nodiscard]] size_t Size() const;

    [[nodiscard]] Iterator Begin() const;
    [[nodiscard]] Iterator End() const;

    class Iterator {
    public:

        Iterator(ListNode* pNode);

        Iterator& operator++();

        std::string& operator*();

        friend bool operator==(const List::Iterator& A, const List::Iterator& B);

        friend bool operator!=(const List::Iterator& A, const List::Iterator& B);
    private:
        ListNode* _pNode;
    };
};
