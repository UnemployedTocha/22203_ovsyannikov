#include "Over.h"
#include "FactoryInitializer.h"

void Over::Execute(Operands& operands, Tokens& tokens, std::string& output, Reader& reader) {
    int operand1 = operands.GetAndPop();
    int operand2 = operands.Top();

    operands.Push(operand1);
    operands.Push(operand2);

}

namespace {
    FactoryInitializer<Over> Registration("over");
}