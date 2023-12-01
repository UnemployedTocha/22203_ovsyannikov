#include <stdexcept>
#include "FactoryInitializer.h"
#include "Dup.h"

void Dup::Execute(std::stack<int>& numbers_, std::ifstream& inputFile) {
    int operand1;
    if(numbers_.empty()){
        throw std::underflow_error("Stack underflow!");
    }
    operand1 = numbers_.top();

    numbers_.push(operand1);
}

namespace {
    FactoryInitializer<Dup> Registration("dup");
}