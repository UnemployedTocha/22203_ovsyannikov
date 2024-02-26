#include "StringOutput.h"
#include <iostream>
#include "FactoryComplexFuncInitializer.h"
#include <fstream>
#include <exception>

void StringOutput::Execute(Operands& operands, Tokens& tokens, std::string& output, Reader& reader){
    if(!tokens.IsEmpty()) {
        std::string token = tokens.GetAndPop();
        if(token.back() == '"') {
            output += token;
            output.pop_back();
            return;
        }
    }
    throw std::runtime_error("String is incorrect");
}

void StringOutput::Check(Tokens& tokens, Reader& reader) {
    if(!tokens.IsEmpty()) {
        std::string token = tokens.GetAndPop();
        if(token.back() == '"') {
            return;
        }
    }
    throw std::runtime_error("String is incorrect");
}
namespace {
    FactoryComplexFuncInitializer<StringOutput> Registration(".\"");
}