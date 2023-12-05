#include "Dot.h"
#include <stdexcept>
#include "FactoryInitializer.h"

void Dot::Execute(Operands& operands, Tokens& tokens, std::string& output, Reader& reader) {
    int operand = operands.GetAndPop();
    output += std::to_string(operand);
    output += " ";
}

namespace {
    FactoryInitializer<Dot> Registration(".");
}