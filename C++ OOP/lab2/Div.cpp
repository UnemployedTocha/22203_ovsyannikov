#include <stdexcept>
#include "FactoryInitializer.h"
#include "Div.h"

void Div::Execute(Operands& operands, Tokens& tokens, std::string& output, Reader& reader) {
    int operand1 = operands.GetAndPop();
    int operand2 = operands.GetAndPop();

    if(operand1 == 0) {
        throw std::runtime_error("Error: division by zero");
    }

    operands.Push(operand2 / operand1);

}

namespace {
    FactoryInitializer<Div> Registration("/");
}