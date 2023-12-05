#include <stdexcept>
#include "swap.h"
#include "FactoryInitializer.h"

void Swap::Execute(Operands& operands, Tokens& tokens, std::string& output, Reader& reader) {
    int operand1 = operands.GetAndPop();
    int operand2 = operands.GetAndPop();

    operands.Push(operand2);
    operands.Push(operand1);
}

namespace {
    FactoryInitializer<Swap> Registration("swap");
}