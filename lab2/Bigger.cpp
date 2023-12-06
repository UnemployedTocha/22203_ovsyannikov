#include "Bigger.h"
#include <stdexcept>
#include "FactoryInitializer.h"

void Bigger::Execute(Operands& operands, Tokens& tokens, std::string& output, Reader& reader) {
    int operand1 = operands.GetAndPop();
    int operand2 = operands.GetAndPop();

    operands.Push(operand2 > operand1);
}

namespace {
    FactoryInitializer<Bigger> Registration(">");
}