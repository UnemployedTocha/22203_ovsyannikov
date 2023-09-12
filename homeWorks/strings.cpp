#include <iostream>
#include <string>
#include<cstring>

class Strings {
public:
    Strings(){
        str = nullptr;
        _length = 0;
    }
    Strings(const char* incomingStr){
        _length = strlen(incomingStr);
        str = new char[_length + 1];
        memcpy(str, incomingStr, _length+1);
    }
    Strings(const Strings &incomingStr){
        _length = incomingStr._length;
        str = new char[_length];
        memcpy(str, incomingStr.str, _length+1);
    }

    Strings& operator= (const Strings &incomingStr){
        if(this == &incomingStr){
            return *this;
        }
        if(nullptr != this){
            delete[] str;
        }
        _length = incomingStr._length;
        str = new char[_length + 1];
        memcpy(str, incomingStr.str, _length+1);
        return *this;
    }

    void Print_String(){
        std::cout << this -> str << std::endl;
    }

    ~Strings(){
        delete[] str;      
    }
private:
    char* str;
    int _length;

    bool Is_Empty(Strings incomingStr){
        if(nullptr == incomingStr.str){
            return true;
        }
    return false;
    }
};

int main(){
    Strings myString2("abcd");
    Strings myString1("123");
    myString2.Print_String();

    myString1 = myString2;
    myString1.Print_String();
    return 0;
}