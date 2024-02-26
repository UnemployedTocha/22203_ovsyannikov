#pragma once

#include "Factory.h"
#include "Command.h"

class Loop : public Command {
public:
    void Execute(Operands& operands, Tokens& tokens, std::string& output, Reader& reader) override;
    void Check(Tokens& tokens, Reader& reader) override;
private:
    static void GetTokensToLoop(Tokens& tokens, std::queue<std::string>& tokensToLoop);
};