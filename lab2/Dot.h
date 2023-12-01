#pragma once

#include "Factory.h"
#include "Command.h"

class Dot : public Command {
public:
    void Execute(std::stack<int>& numbers_, std::ifstream& inputFile);
};
