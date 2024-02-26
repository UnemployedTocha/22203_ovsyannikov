#pragma once

#include <string>
#include "Operands.h"

class Interpreter {
public:
    Interpreter() = default;
    void TextProccesing(std::istream& inputFile, std::string& output);

private:
    Operands operands_;
};