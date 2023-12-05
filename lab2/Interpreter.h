#pragma once

#include <fstream>
#include <string>
#include <stack>
#include "Operands.h"

class Interpreter {
public:
    Interpreter() = default;
    void TextProccesing(std::ifstream& inputFile, std::string& output);

private:
    Operands operands_;
};