#include <iostream>
#include <stdexcept>
#include "FactoryInitializer.h"
#include "Emit.h"


void Emit::Execute(std::stack<int>& numbers_, std::ifstream& inputFile) {
    int operand1;
    if(numbers_.empty()){
        throw std::underflow_error("Stack underflow!");
    }
    operand1 = numbers_.top();
    numbers_.pop();

    std::cout << static_cast<char>(operand1) << std::endl;
}

namespace {
    FactoryInitializer<Emit> Registration("emit");
}
