#include "FactoryInitializer.h"
#include "Mod.h"

void Mod::Execute(Operands& operands, Tokens& tokens, std::string& output, Reader& reader) {
    int operand1 = operands.GetAndPop();
    int operand2 = operands.Top();

    operands.Push(operand1);

    operands.Push(operand2 % operand1);
}
namespace {
    FactoryInitializer<Mod> Registration("mod");
}