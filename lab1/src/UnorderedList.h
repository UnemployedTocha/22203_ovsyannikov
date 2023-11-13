#pragma once

#include <string>

class Value {
private:
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
private:
    struct ListNode {
        std::string key;
        Value data; 
        struct ListNode* pNext = nullptr;
    };
public:
    class Iterator;

    List();
    List(const std::string& key,const Value& data);
    List(const List& L);
    List(List&& L) noexcept;
    List& operator=(const List& L);
    List& operator=(List&& L);
    ~List();
    void Push(const std::string& key,const Value& data);
    bool Erase(const std::string& key);
    bool Contains(const std::string& key) const;
    Value& ValueByKey(const std::string& key); 

    bool IsEmpty() const;
    void PrintList() const;
    size_t Size() const;
    

    Iterator Begin();
    Iterator End();

    class Iterator {
    public:
        Iterator() : _pNode(nullptr) {};
        Iterator(ListNode* pNode) : _pNode(pNode) {};
        Iterator& operator++() {
            if(!_pNode) {
                return *this;
            }
            _pNode = _pNode -> pNext;
            return *this; 
        }
    private:
        ListNode* _pNode;
    };
private:
    ListNode* _pFirstNode = nullptr;
    size_t _sz = 0;

    
    ListNode* NewNode(const std::string& key,const Value& data);
    void FillNode(ListNode* pNodeFrom, ListNode* pNodeTo);
    void CopyList(const List& L);
    void FreeList();

    void Push(ListNode& N);
    ListNode* Pop();
    // ListNode* GetFirstNodePointer() const;

};