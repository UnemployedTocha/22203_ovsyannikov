#pragma once

#include "Factory.h"
#include "Command.h"

class If : public Command {
public:
    void Execute(Operands& operands, Tokens& tokens, std::string& output, Reader& reader) override;
    void Check(Tokens& tokens, Reader& reader) override;
};