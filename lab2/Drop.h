#pragma once

#include "Factory.h"
#include "Command.h"

class Drop : public Command {
public:
    void Execute(Operands& operands, Tokens& tokens, std::string& output, Reader& reader);
};
