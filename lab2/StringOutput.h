#pragma once

#include "Factory.h"
#include "Command.h"

class StringOutput : public Command {
public:
    void Execute(std::stack<int>& numbers_, Tokens& tokens, std::string& output, Reader& reader);
    void Check(Tokens& tokens, Reader& reader);
};