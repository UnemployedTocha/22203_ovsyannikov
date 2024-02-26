#include "Sum.h"
#include "FactoryInitializer.h"

void Sum::Execute(Operands& operands, Tokens& tokens, std::string& output, Reader& reader) {
    int operand1 = operands.GetAndPop();
    int operand2 = operands.GetAndPop();
    operands.Push(operand1 + operand2);
}

namespace {
    FactoryInitializer<Sum> Registration("+");
}