#include "Rot.h"
#include <stdexcept>
#include "FactoryInitializer.h"

void Rot::Execute(std::stack<int>& numbers_, Tokens& tokens, std::string& output, Reader& reader) {
    int operand1;
    int operand2;
    int operand3;

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

    if(numbers_.empty()){
        throw std::underflow_error("Stack underflow!");
    }
    operand3 = numbers_.top();
    numbers_.pop();

    numbers_.push(operand2);
    numbers_.push(operand1);
    numbers_.push(operand3);

}

namespace {
    FactoryInitializer<Rot> Registration("rot");
}