#include "Cr.h"
#include "FactoryInitializer.h"

void Cr::Execute(Operands& operands, Tokens& tokens, std::string& output, Reader& reader){
    output += "\n";
}

namespace {
    FactoryInitializer<Cr> Registration("cr");
}