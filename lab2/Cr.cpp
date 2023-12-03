#include "Cr.h"
#include <iostream>
#include "FactoryInitializer.h"

void Cr::Execute(std::stack<int>& numbers_, Tokens& tokens, std::string& output, Reader& reader){
    output += "\n";
}

namespace {
    FactoryInitializer<Cr> Registration("cr");
}