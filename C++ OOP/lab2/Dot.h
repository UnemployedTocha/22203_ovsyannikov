#pragma once

#include "Factory.h"
#include "Command.h"

class Dot : public Command {
public:
    void Execute(Operands& operands, Tokens& tokens, std::string& output, Reader& reader);
};
