#include "Operands.h"
#include <stdexcept>

int Operands::GetAndPop() {
    if(operands_.empty()){
        throw std::underflow_error("Stack underflow!");
    }
    int operand = operands_.top();
    operands_.pop();
    return operand;
}

int Operands::Top() {
    if(operands_.empty()){
        throw std::underflow_error("Stack underflow!");
    }
    return operands_.top();
}
void Operands::Push(int operand) {
    operands_.push(operand);
}