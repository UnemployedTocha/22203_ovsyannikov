#include "Less.h"
#include "FactoryInitializer.h"


void Less::Execute(Operands& operands, Tokens& tokens, std::string& output, Reader& reader) {
    int operand1 = operands.GetAndPop();
    int operand2 = operands.GetAndPop();
    operands.Push(operand2 < operand1);

}

namespace {
    FactoryInitializer<Less> Registration("<");
}