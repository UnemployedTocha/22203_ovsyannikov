#include <iostream>
#include <string>
#include<cstring>

class Strings {
public:
    Strings(){
        str = nullptr;
        _length = 0;
    }
    Strings(char* incomingStr){
        _length = strlen(incomingStr);
        str = new char[_length + 1];
        memcpy(str, incomingStr, _length+1);
    }
    Strings(Strings &incomingStr){
        _length = incomingStr._length;
        str = incomingStr.str;
    }



    void PrintString(){
        std::cout << str << std::endl;
    }

    ~Strings(){

    }
private:
    char* str;
    int _length;

};

int main(){
    return 0;
}