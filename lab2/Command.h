#pragma once

#include "Reader.h"
#include "Tokens.h"
#include <stack>

class Command {
public:
    Command();
    virtual void Execute(std::stack<int>& numbers_, Tokens& tokens, std::string& output, Reader& reader);
    virtual void Check(Tokens& tokens, Reader& reader);
    virtual ~Command();
};
