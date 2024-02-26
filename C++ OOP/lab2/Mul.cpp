#include "Mul.h"
#include "FactoryInitializer.h"

void Mul::Execute(Operands& operands, Tokens& tokens, std::string& output, Reader& reader) {
    int operand1 = operands.GetAndPop();
    int operand2 = operands.GetAndPop();

    operands.Push(operand2 * operand1);
}

namespace {
    FactoryInitializer<Mul> Registration("*");
}