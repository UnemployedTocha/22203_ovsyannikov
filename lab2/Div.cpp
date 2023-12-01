#include <stdexcept>
#include "FactoryInitializer.h"
#include "Div.h"

void Div::Execute(std::stack<int>& numbers_, std::ifstream& inputFile) {
    int operand1;
    int operand2;
    if(numbers_.empty()){
        throw std::underflow_error("Stack underflow!");
    }
    operand1 = numbers_.top();
    if(operand1 == 0) {
        throw std::runtime_error("Error: division by zero");
    }
    numbers_.pop();

    if(numbers_.empty()){
        throw std::underflow_error("Stack underflow!");
    }
    operand2 = numbers_.top();
    numbers_.pop();

    numbers_.push(operand2 / operand1);

}

namespace {
    FactoryInitializer<Div> Registration("/");
}