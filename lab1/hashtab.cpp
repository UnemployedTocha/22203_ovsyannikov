#include <iostream>
#include <string>

typedef std::string Key;

struct Value {
    unsigned age;
    unsigned weight;
};

class HashTable{
public:
    HashTable();
    ~HashTable();

    HashTable(const HashTable& b);
    HashTable(const HashTable&& b);

    void swap(HashTable& b);

    HashTable& operator=(const HashTable& b);

    void clear();
    
    bool errase(const Key& k);

    bool insert(const Key& k, const Value& v);

    bool contains(const Key& k) const;

    Value& operator[](const Key& k);

    Value& at(const Key& k);
    const Value& at(const Key& k) const;

    size_t size() const;
    bool empty() const;

    friend bool operator==(const HashTable& a, const HashTable& b);
    friend bool operator!=(const HashTable& a, const HashTable& b);

private:


};




int main(){

    return 0;
}