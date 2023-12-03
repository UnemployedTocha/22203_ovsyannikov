#pragma once

#include "Factory.h"
#include "Command.h"

class Cr : public Command {
public:
    void Execute(std::stack<int>& numbers_, Tokens& tokens, std::string& output, Reader& reader);
};