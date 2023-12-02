#pragma once

#include "Factory.h"
#include "Command.h"

class If : public Command {
public:
    void Execute(std::stack<int>& numbers_, std::ifstream& inputFile);
    bool isNumber(const std::string& str);
};