#include "StringOutput.h"
#include <iostream>
#include "FactoryInitializer.h"
#include <fstream>
#include <exception>

void StringOutput::Execute(std::stack<int>& numbers_, Tokens& tokens, std::string& output, Reader& reader){
    std::string token;
    if(tokens.IsEmpty()) {
        token = tokens.GetAndPop();
        if(token.back() == '"') {
            output += token;
            output.pop_back();
            return;
        }
    }
    throw std::runtime_error("String is incorrect");
}

namespace {
    FactoryInitializer<StringOutput> Registration(".\"");
}