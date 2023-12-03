#include <iostream>
#include <stdexcept>
#include "FactoryInitializer.h"
#include "Emit.h"


void Emit::Execute(std::stack<int>& numbers_, Tokens& tokens, std::string& output, Reader& reader) {
    int operand1;
    if(numbers_.empty()){
        throw std::underflow_error("Stack underflow!");
    }
    operand1 = numbers_.top();
    numbers_.pop();

    output +=  static_cast<char>(operand1);
    output += " ";
}

namespace {
    FactoryInitializer<Emit> Registration("emit");
}
