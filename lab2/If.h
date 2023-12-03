#pragma once

#include "Factory.h"
#include "Command.h"

class If : public Command {
public:
    void Execute(std::stack<int>& numbers_, Tokens& tokens, std::string& output, Reader& reader);
private:
    bool isNumber(const std::string& str);
    static void CheckSemicolon(Tokens& tokens);
    void CheckIf(Tokens& tokens, Reader& reader);
};