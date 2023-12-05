#pragma once

#include "Factory.h"
#include "Command.h"

class Loop : public Command {
public:
    void Execute(std::stack<int>& numbers_, Tokens& tokens, std::string& output, Reader& reader) override;
    void Check(Tokens& tokens, Reader& reader) override;
private:
    void GetTokensToLoop(Tokens& tokens, std::queue<std::string>& tokensToLoop, Reader& reader);
};