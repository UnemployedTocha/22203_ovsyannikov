#include "Cr.h"
#include <iostream>
#include "FactoryInitializer.h"

void Cr::Execute(std::stack<int>& numbers_, std::ifstream& inputFile){
    std::cout << std::endl;
}

namespace {
    FactoryInitializer<Cr> Registration("cr");
}