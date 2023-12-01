#pragma once

#include <stack>
#include <string>

class Command {
public:
    Command();
    virtual void Execute(std::stack<int>& numbers_, std::ifstream& inputFile);
    virtual ~Command();
};
