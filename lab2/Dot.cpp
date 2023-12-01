#include "Dot.h"
#include <stdexcept>
#include "FactoryInitializer.h"
#include <iostream>

void Dot::Execute(std::stack<int>& numbers_, std::ifstream& inputFile) {
    if(numbers_.empty()){
        throw std::underflow_error("Stack underflow!");
    }
    std::cout << numbers_.top() << " ";
    numbers_.pop();
}

namespace {
    FactoryInitializer<Dot> Registration(".");
}