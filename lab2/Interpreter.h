#pragma once

#include <fstream>
#include <string>
#include <stack>
#include <iostream>

#include "Factory.h"

class Interpreter {
public:
    Interpreter() = default;
    void TextProccesing(std::ifstream& inputFile);

private:
    std::stack<int> operands_;

    void PrintStack();
    bool isNumber(const std::string& str);

};