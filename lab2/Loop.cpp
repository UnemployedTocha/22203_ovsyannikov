#include "Loop.h"
#include "Utility.h"
#include "Factory.h"
#include "FactoryComplexFuncInitializer.h"

void Loop::Execute(std::stack<int>& numbers_, Tokens& tokens, std::string& output, Reader& reader) {
    auto pFactory = Factory<Command, std::string, Command *(*)()>::getInstance();
    if (numbers_.empty()) {
        throw std::underflow_error("Stack underflow!");
    }
    int operand1 = numbers_.top();
    numbers_.pop();

    if (numbers_.empty()) {
        throw std::underflow_error("Stack underflow!");
    }
    int operand2 = numbers_.top();
    numbers_.pop();

    std::queue<std::string> tokensToLoop;
    while(!tokens.IsEmpty()) {
        std::string token = tokens.GetAndPop();
        if(isNumber(token) || pFactory->isRegist3red(token) || (token == "i")) {
            tokensToLoop.push(token);
        }
        else {
            token += " ?";
            throw std::runtime_error(token);
        }
    }

}

void Loop::Check(Tokens& tokens, Reader& reader) {

}

void GetTokensToLoop(Tokens& tokens, std::queue<std::string>& tokensToLoop, Reader& reader) {

}

namespace {
    FactoryComplexFuncInitializer<Loop> Registration("do");
}
