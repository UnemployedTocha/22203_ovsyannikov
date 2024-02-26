#pragma once

#include "Operands.h"
#include "Reader.h"
#include "Tokens.h"

class Command {
public:
    Command();
    virtual void Execute(Operands& operands, Tokens& tokens, std::string& output, Reader& reader);
    virtual void Check(Tokens& tokens, Reader& reader);
    virtual ~Command();
};
