#include <stdexcept>
#include "FactoryInitializer.h"
#include "Emit.h"


void Emit::Execute(Operands& operands, Tokens& tokens, std::string& output, Reader& reader) {
    int operand1 = operands.GetAndPop();
    output +=  static_cast<char>(operand1);
    output += " ";
}

namespace {
    FactoryInitializer<Emit> Registration("emit");
}
