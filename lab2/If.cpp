#include "If.h"
#include "FactoryComplexFuncInitializer.h"
#include "Utility.h"
#include <fstream>

void If::Execute(std::stack<int>& numbers_, Tokens& tokens, std::string& output, Reader& reader) {
    auto pFactory = Factory<Command, std::string, Command *(*)()>::getInstance();
    Tokens tempTokens(tokens);

    if (numbers_.empty()) {
        throw std::underflow_error("Stack underflow!");
    }

    int operand = numbers_.top();
    if (operand == 0) {
        while (!tokens.IsEmpty()) {
            std::string token = tokens.GetAndPop();
            if(pFactory->isComplexFuncRegist3red(token)) {
                (pFactory->createProductByName(token)) -> Check(tokens, reader);
            } else if (token == "else") {
                while (!tokens.IsEmpty()) {
                    token = tokens.GetAndPop();
                    if (isNumber(token)) {
                        numbers_.push(std::stoi(token));
                    }
                    else if(pFactory->isRegist3red(token)) {
                        Command *pCommand = pFactory->createProductByName(token);
                        pCommand->Execute(numbers_, tokens, output, reader);
                    }
                    else if (token == "else") {
                        throw std::runtime_error("Incorrect number of \"else\"");
                    }
                    else if (token == "then") {
                        CheckSemicolon(tokens);
                        return;
                    } else {
                        token += " ?";
                        throw std::runtime_error(token);
                    }
                }
            } else if (token == "then") {
                CheckSemicolon(tokens);
                return;
            } else if(!pFactory->isRegist3red(token) && !isNumber(token)) {
                token += " ?";
                throw std::runtime_error(token);
            }
        }
        throw std::runtime_error("Incorrect form of condition");
    }
    else {
        while (!tokens.IsEmpty()) {
            std::string token = tokens.GetAndPop();
            if (isNumber(token)) {
                numbers_.push(std::stoi(token));
            } else if(pFactory->isRegist3red(token)) {
                Command *pCommand = pFactory->createProductByName(token);
                pCommand->Execute(numbers_, tokens, output, reader);
            } else if(token == "else") {
                while(!tokens.IsEmpty()) {
                    token = tokens.GetAndPop();
                    if(pFactory->isComplexFuncRegist3red(token)) {
                        (pFactory->createProductByName(token)) -> Check(tokens, reader);
                    }
                    else if (pFactory->isRegist3red(token) || isNumber(token)) {
                        continue;
                    } else if(token == "else") {
                        throw std::runtime_error("Incorrect number of \"else\"");
                    } else if (token == "then") {
                        CheckSemicolon(tokens);
                        return;
                    } else {
                        token += " ?";
                        throw std::runtime_error(token);
                    }
                }
            } else if(token == "then") {
                CheckSemicolon(tokens);
                return;
            } else {
                token += " ?";
                throw std::runtime_error(token);
            }
        }
    }
    throw std::runtime_error("There is no then at the end of condition");
}

void If::Check(Tokens& tokens, Reader& reader) {
    auto pFactory = Factory<Command, std::string, Command *(*)()>::getInstance();
    while (!tokens.IsEmpty()) {
        std::string token = tokens.GetAndPop();
        if(pFactory->isComplexFuncRegist3red(token)) {
            (pFactory->createProductByName(token)) -> Check(tokens, reader);
        }
        else if (token == "else") {
            while (!tokens.IsEmpty()) {
                token = tokens.GetAndPop();
                if(pFactory->isComplexFuncRegist3red(token)) {
                    (pFactory->createProductByName(token)) -> Check(tokens, reader);
                } else if (token == "else") {
                    throw std::runtime_error("Incorrect number of \"else\"");
                } else if (token == "then") {
                    CheckSemicolon(tokens);
                    return;
                } else if (!isNumber(token) && !pFactory->isRegist3red(token)){
                    token += " ?";
                    throw std::runtime_error(token);
                }
            }
        } else if (token == "then") {
            CheckSemicolon(tokens);
            return;
        } else if(!isNumber(token) && !pFactory->isRegist3red(token)) {
            token += " ?";
            throw std::runtime_error(token);
        }
    }
    throw std::runtime_error("Incorrect form of condition");
}

namespace {
    FactoryComplexFuncInitializer<If> Registration("if");
}