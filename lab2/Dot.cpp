#include "Dot.h"
#include <stdexcept>
#include "FactoryInitializer.h"

void Dot::Execute(std::stack<int>& numbers_, Tokens& tokens, std::string& output, Reader& reader) {
    if(numbers_.empty()){
        throw std::underflow_error("Stack underflow!");
    }
    output += std::to_string(numbers_.top());
    output += " ";
    numbers_.pop();

}

namespace {
    FactoryInitializer<Dot> Registration(".");
}