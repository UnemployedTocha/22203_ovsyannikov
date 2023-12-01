#include <stdexcept>
#include "Sum.h"
#include "FactoryInitializer.h"

void Sum::Execute(std::stack<int>& numbers_, std::ifstream& inputFile) {
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

    numbers_.push(operand1 + operand2);

}

namespace {
    FactoryInitializer<Sum> Registration("+");
}