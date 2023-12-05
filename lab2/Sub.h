#pragma once

#include "Factory.h"
#include "Command.h"

class Sub : public Command {
public:
    void Execute(Operands& operands, Tokens& tokens, std::string& output, Reader& reader) override;
};