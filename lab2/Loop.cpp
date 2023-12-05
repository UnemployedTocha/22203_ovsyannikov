#include "Loop.h"
#include "Utility.h"
#include "Factory.h"
#include "FactoryComplexFuncInitializer.h"
#include <memory>

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
    GetTokensToLoop(tokens, tokensToLoop);

    for(int i = operand1; i < operand2; ++i) {
        auto tempTokens = tokensToLoop;
        while(!tempTokens.empty()) {
            std::string token = tempTokens.front();
            tempTokens.pop();
            if(isNumber(token)) {
                numbers_.push(std::stoi(token));
            } else if(token == "i") {
                numbers_.push(i);
            }
            else {
                auto pCommand = std::unique_ptr<Command>(pFactory->createProductByName(token));
                pCommand->Execute(numbers_, tokens, output, reader);
            }
        }
    }
}

void Loop::Check(Tokens& tokens, Reader& reader) {
    auto pFactory = Factory<Command, std::string, Command *(*)()>::getInstance();
    while(!tokens.IsEmpty()) {
        std::string token = tokens.GetAndPop();
        if(pFactory->isComplexFuncRegist3red(token)) {
            auto pCommand = std::unique_ptr<Command>(pFactory->createProductByName(token));
            pCommand->Check(tokens, reader);
        } else if(token == "loop") {
            CheckSemicolon(tokens);
            return;
        }
        else if(!isNumber(token) && !pFactory->isRegist3red(token) && token != "i"){
            token += " ?";
            throw std::runtime_error(token);
        }
    }
    throw std::runtime_error("There is no \"loop ;\" at the end of \"do\"");
}

void Loop::GetTokensToLoop(Tokens& tokens, std::queue<std::string>& tokensToLoop) {
    auto pFactory = Factory<Command, std::string, Command *(*)()>::getInstance();
    while(!tokens.IsEmpty()) {
        std::string token = tokens.GetAndPop();
        if(isNumber(token) || pFactory->isRegist3red(token) || (token == "i")) {
            tokensToLoop.push(token);
        } else if(token == "loop") {
            CheckSemicolon(tokens);
            return;
        }

        else {
            token += " ?";
            throw std::runtime_error(token);
        }
    }
    throw std::runtime_error("There is no \"loop ;\" at the end of \"do\"");
}

namespace {
    FactoryComplexFuncInitializer<Loop> Registration("do");
}
