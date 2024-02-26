#include "Drop.h"
#include <stdexcept>
#include "FactoryInitializer.h"

void Drop::Execute(Operands& operands, Tokens& tokens, std::string& output, Reader& reader) {
    operands.GetAndPop();
}

namespace {
    FactoryInitializer<Drop> Registration("drop");
}