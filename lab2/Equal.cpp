#include "Equal.h"
#include <stdexcept>
#include "FactoryInitializer.h"


void Equal::Execute(Operands& operands, Tokens& tokens, std::string& output, Reader& reader) {
    int operand1 = operands.GetAndPop();
    int operand2 = operands.GetAndPop();
    operands.Push(operand2 == operand1);

}

namespace {
    FactoryInitializer<Equal> Registration("=");
}