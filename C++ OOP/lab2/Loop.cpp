#include "Loop.h"
#include "Utility.h"
#include "Factory.h"
#include "FactoryComplexFuncInitializer.h"
#include <memory>

void Loop::Execute(Operands& operands, Tokens& tokens, std::string& output, Reader& reader) {
    auto pFactory = Factory<Command, std::string, Command *(*)()>::getInstance();

    int operand1 = operands.GetAndPop();
    int operand2 = operands.GetAndPop();

    std::queue<std::string> tokensToLoop;
    GetTokensToLoop(tokens, tokensToLoop);

    for(int i = operand1; i < operand2; ++i) {
        auto tempTokens = tokensToLoop;
        while(!tempTokens.empty()) {
            std::string token = tempTokens.front();
            tempTokens.pop();
            if(isNumber(token)) {
                operands.Push(std::stoi(token));
            } else if(token == "i") {
                operands.Push(i);
            }
            else {
                auto pCommand = std::unique_ptr<Command>(pFactory->createProductByName(token));
                pCommand->Execute(operands, tokens, output, reader);
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
