#include <stdexcept>
#include "FactoryInitializer.h"
#include "Dup.h"

void Dup::Execute(Operands& operands, Tokens& tokens, std::string& output, Reader& reader) {
    int operand1 = operands.Top();
    operands.Push(operand1);
}

namespace {
    FactoryInitializer<Dup> Registration("dup");
}