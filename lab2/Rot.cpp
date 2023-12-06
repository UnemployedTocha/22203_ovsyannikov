#include "Rot.h"
#include "FactoryInitializer.h"

void Rot::Execute(Operands& operands, Tokens& tokens, std::string& output, Reader& reader) {
    int operand1 = operands.GetAndPop();
    int operand2 = operands.GetAndPop();
    int operand3 = operands.GetAndPop();

    operands.Push(operand2);
    operands.Push(operand3);
    operands.Push(operand1);

}

namespace {
    FactoryInitializer<Rot> Registration("rot");
}