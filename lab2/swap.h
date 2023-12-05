#pragma once

#include "Factory.h"
#include "Command.h"

class Swap : public Command {
public:
    void Execute(Operands& operands, Tokens& tokens, std::string& output, Reader& reader) override;
};
