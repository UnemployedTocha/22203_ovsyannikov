#include "Equal.h"
#include <stdexcept>
#include "FactoryInitializer.h"


void Equal::Execute(std::stack<int>& numbers_, Tokens& tokens, std::string& output, Reader& reader) {
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

    numbers_.push(operand2 == operand1);

}

namespace {
    FactoryInitializer<Equal> Registration("=");
}