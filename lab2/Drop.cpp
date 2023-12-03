#include "Drop.h"
#include <stdexcept>
#include "FactoryInitializer.h"

void Drop::Execute(std::stack<int>& numbers_, Tokens& tokens, std::string& output, Reader& reader) {
    if(numbers_.empty()){
        throw std::underflow_error("Stack underflow!");
    }
    numbers_.pop();
}

namespace {
    FactoryInitializer<Drop> Registration("drop");
}