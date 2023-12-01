#include <stdexcept>
#include "Mul.h"
#include "FactoryInitializer.h"

void Mul::Execute(std::stack<int>& numbers_, std::ifstream& inputFile) {
    int operand1;
    int operand2;
    if(numbers_.empty()){
        throw std::underflow_error("Stack underflow!");
    }
    operand1 = numbers_.top();
    numbers_.pop();

    if(numbers_.empty()){
        throw std::underflow_error("Stack underflow!");
    }
    operand2 = numbers_.top();
    numbers_.pop();

//    (operand1 > 0) ? assert(operand2 <= INT_MAX - operand1) : assert(operand2 >= INT_MIN - operand1);
    numbers_.push(operand2 * operand1);
}

namespace {
    FactoryInitializer<Mul> Registration("*");
}