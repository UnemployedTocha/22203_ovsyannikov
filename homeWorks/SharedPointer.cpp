#include <iostream>

class A {
public:
    A() : _someNumber(0){}

    size_t DoSmt(){
        _someNumber += 10;
        return _someNumber;
    }

private:
    size_t _someNumber;    
};


template <class T>
class MySharedPointer {
public:
    MySharedPointer() : _ptr(nullptr), _count(nullptr) {}
    MySharedPointer(T* a) : _ptr(a){
        _count = new size_t;
        *_count = 1;
    }

    MySharedPointer(const MySharedPointer& other) : _ptr(other._ptr), _count(other._count){
        ++(*_count);
    }

    MySharedPointer& operator=(const MySharedPointer& other) {
        if(&other == this) {
            return *this;
        }
        this -> ~MySharedPointer();
        _ptr = other._ptr;
        
        _count = other._count;
        ++(*_count);
        return *this;
    }
    
    MySharedPointer(MySharedPointer&& other) : _ptr(other._ptr), _count(other._count) {
        other._count = nullptr;
        other._ptr =  nullptr;          
    }
    
    
    T* operator->() {
        return _ptr;
    }
    T& operator*() {
        return *_ptr;
    }
    ~MySharedPointer() {
        if(_count == nullptr){ 
            delete _ptr;
        }
        else if(--(*_count) == 0) {
            delete _ptr;
            delete _count;
        }
    }
    
    T* Get() {
        return _ptr;    
    }
    T* Reset() {
        if(--(*_count) == 0) {
            delete _ptr;
            delete _count;
        }

        _count = new size_t; 
        *_count = 0;
        _ptr = nullptr;
        return _ptr;         
    } 


private:
    T* _ptr;
    size_t* _count;
};



int main(){
    MySharedPointer<A> p1;
    MySharedPointer<A> p2(new A());
    MySharedPointer<A> p3 = p2;
    MySharedPointer<A> p4 = p3;
    MySharedPointer<A> p5 = p4;

    p2 = p1;
    MySharedPointer<A> p6 = p5;
    MySharedPointer<A> p7 = std::move(p6);
    p6 = std::move(p7);
    p5.Reset();


    return 0;
}