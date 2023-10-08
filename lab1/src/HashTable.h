#pragma once
#include <iostream>
#include <string>
#include "UnorderedList.h"

typedef std::string Key;
#define DEAFULT_SIZE_CAP 4


class HashTable{
public:
    HashTable();
    ~HashTable();
    HashTable(const HashTable& b);
    HashTable(const HashTable&& b);

    // Обменивает значения двух хэш-таблиц.
    // Подумайте, зачем нужен этот метод, при наличии стандартной функции
    // std::swap.
    void swap(HashTable& b);
    HashTable& operator=(const HashTable& b);

    // Очищает контейнер.
    void clear();

    // Удаляет элемент по заданному ключу.

    bool erase(const Key& k);

    // Вставка в контейнер. Возвращаемое значение - успешность вставки.
    bool insert(const Key& k, const Value& v);

    // Проверка наличия значения по заданному ключу.
    bool contains(const Key& k) const;
    // Возвращает значение по ключу. Небезопасный метод.
    // В случае отсутствия ключа в контейнере, следует вставить в контейнер
    // значение, созданное конструктором по умолчанию и вернуть ссылку на него.
        Value& operator[](const Key& k);
    // Возвращает значение по ключу. Бросает исключение при неудаче.
    Value& at(const Key& k);
    const Value& at(const Key& k) const;
    size_t size() const;
    bool empty() const;
    friend bool operator==(const HashTable& a, const HashTable& b);
    friend bool operator!=(const HashTable& a, const HashTable& b);
private:    
    List* _arr = nullptr;
    size_t _cap = 0;
    size_t _sz = 0;
    
    void Resize(size_t newSize);
    void Insert(std::string key, Value data, size_t index);
};