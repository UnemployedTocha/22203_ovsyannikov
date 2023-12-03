#include <stdexcept>
#include "FactoryInitializer.h"
#include "Mod.h"

void Mod::Execute(std::stack<int>& numbers_, Tokens& tokens, std::string& output, Reader& reader) {
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
    numbers_.push(operand1);

    numbers_.push(operand2 % operand1);
}
namespace {
    FactoryInitializer<Mod> Registration("mod");
}