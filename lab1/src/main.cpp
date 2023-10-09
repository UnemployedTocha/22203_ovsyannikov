#include <iostream>
#include <string>
#include "HashTable.h"


int main(){
    Value P1(10,20);
    Value P2(20, 70);
    List A("123", P1);
    A.Push("qwerty", P2);
    A.PrintList();
    return 0;
}