#include <stdexcept>
#include "swap.h"
#include "FactoryInitializer.h"

void Swap::Execute(std::stack<int>& numbers_, std::ifstream& inputFile) {
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

    numbers_.push(operand2);
    numbers_.push(operand1);

}

namespace {
    FactoryInitializer<Swap> Registration("swap");
}