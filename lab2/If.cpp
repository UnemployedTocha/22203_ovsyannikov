#include "If.h"
#include <iostream>
#include "FactoryInitializer.h"
#include <fstream>
#include <exception>

 void If::CheckSemicolon(Tokens& tokens) {
    if(tokens.IsEmpty()) {
        throw std::runtime_error("There is no ; at the end of condition");
    }
    std::string token = tokens.GetAndPop();
    if(token != ";") {
        throw std::runtime_error("There is no ; at the end of condition");
    }
}

//void If::CheckIf(Tokens& tokens, Reader& reader) {
//    Tokens tempTokens(tokens);
//    int ifCounter = 1;
//
//    while(!tempTokens.IsEmpty()) {
//        std::string token = tempTokens.GetAndPop();
//        if(token == "if") {
//            ++ifCounter;
//        }
//        if(token == "then") {
//            --ifCounter;
//        }
//        if(ifCounter < 0) {
//            throw std::runtime_error("Then before if");
//        }
//    }
//    if(ifCounter != 0) {
//        throw std::runtime_error("Incorrect form of condition");
//    }
//}

void If::Execute(std::stack<int>& numbers_, Tokens& tokens, std::string& output, Reader& reader) {
    Factory<Command, std::string, Command *(*)()> *pFactory = Factory<Command, std::string, Command *(*)()>::getInstance();

    int operand;
    if (numbers_.empty()) {
        throw std::underflow_error("Stack underflow!");
    }
    operand = numbers_.top();

    if (operand == 0) {
        while (!tokens.IsEmpty()) {
            std::string token = tokens.GetAndPop();

            if (pFactory->isRegist3red(token) || isNumber(token)) {
                continue;
            } else if (token == "else") {
                while (!tokens.IsEmpty()) {
                    token = tokens.GetAndPop();
                    if (isNumber(token)) {
                        numbers_.push(std::stoi(token));
                    } else if (pFactory->isRegist3red(token)) {
                        Command *pCommand = pFactory->createProductByName(token);
                        try {
                            pCommand->Execute(numbers_, tokens, output, reader);
                        } catch (std::underflow_error const &ex) {
                            std::cout << ex.what() << std::endl;
                            return;
                        } catch (std::runtime_error const &ex) {
                            std::cout << ex.what();
                        }
                    } else if (token == "then") {
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
            } else {
                token += " ?";
                throw std::runtime_error(token);
            }
        }
    }

    else {
        while(!tokens.IsEmpty()) {
            std::string token = tokens.GetAndPop();
            if (isNumber(token)) {
                numbers_.push(std::stoi(token));
            } else if (pFactory->isRegist3red(token)) {
                Command *pCommand = pFactory->createProductByName(token);
                try {
                    pCommand->Execute(numbers_, tokens, output, reader);
                } catch (std::underflow_error const &ex) {
                    std::cout << ex.what() << std::endl;
                    return;
                } catch (std::runtime_error const &ex) {
                    std::cout << ex.what();
                }
            } else if(token == "else") {
                while(!tokens.IsEmpty()) {
                    token = tokens.GetAndPop();
                    if (pFactory->isRegist3red(token) || isNumber(token) || token == "else") {
                        continue;
                    } else if (token == "then") {
                        CheckSemicolon(tokens);
                        return;
                    } else {
                        token += " ?";
                        throw std::runtime_error(token);
                    }
                }
            }
            else if(token == "then") {
                CheckSemicolon(tokens);
                return;
            } else {
                token += " ?";
                throw std::runtime_error(token);
            }
        }
    }
//    throw std::runtime_error("There is no then at the end of condition");
}


bool If::isNumber(const std::string& str) {
    if(str.empty()) {
        return false;
    }

    if(str[0] == '-' && str.length() == 1) {
        return false;
    }

    for(size_t i = 0; i < str.length(); ++i) {
        if(i == 0 && str[i] == '-') {
            continue;
        }
        if(!std::isdigit(str[i])) {
            return false;
        }
    }
    return true;
}


namespace {
    FactoryInitializer<If> Registration("if");
}