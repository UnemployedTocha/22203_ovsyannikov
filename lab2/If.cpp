#include "If.h"
#include <iostream>
#include "FactoryInitializer.h"
#include <fstream>
#include <exception>

void If::Execute(std::stack<int>& numbers_, std::ifstream& inputFile){
    Factory<Command, std::string, Command *(*)()>* pFactory =  Factory<Command, std::string, Command *(*)()>::getInstance();

    int operand;
    if(numbers_.empty()){
        throw std::underflow_error("Stack underflow!");
    }
    operand = numbers_.top();

    std::string branchToExecute;
    std::string token;
    char ch;

    if(operand == 0) {
        while(inputFile.get(ch)) {
            if(ch == '\n') {
                throw std::runtime_error("Incorrect form of condition");
            }

            if(ch == ' ') {
                if(isNumber(token)) {
                    token.clear();
                }
                else if(pFactory->isRegist3red(token)) {
                    token.clear();
                }
                else if(token == "else") {
                    token.clear();
                    while(inputFile.get(ch)) {
                        if(ch == '\n') {
                            throw std::runtime_error("Incorrect form of condition");
                        }
                        if (ch == ' ') {
                            if (isNumber(token)) {
                                numbers_.push(std::stoi(token));
                                token.clear();
                            }
                            else if (pFactory->isRegist3red(token)) {
                                Command *pCommand = pFactory->createProductByName(token);
                                try {
                                    pCommand->Execute(numbers_, inputFile);
                                } catch (std::underflow_error const &ex) {
                                    std::cout << ex.what() << std::endl;
                                    return;
                                } catch (std::runtime_error const &ex) {
                                    std::cout << ex.what();
                                    return;
                                }
                                token.clear();
                            }
                            else if(token == "then") {
                                inputFile >> token;
                                if(token == ";") {
                                    return;
                                }
                                else {
                                    throw std::runtime_error("There is no ; at the end of the condition");
                                }
                            }
                            else if(!token.empty()) {
                                token += "?";
                                throw std::runtime_error(token);
                            }
                        }
                        else {
                            token += ch;
                        }
                    }
                }
                else if(token == "then") {
                    std::cout << token << " ";
                    inputFile >> token;
                    if(token == ";") {
                        std::cout << token << " ";
                        return;
                    }
                    else {
                        throw std::runtime_error("There is no ; at the end of the condition");
                    }
                }
                else if(!token.empty()) {
                    token += "?";
                    throw std::runtime_error(token);
                }
            }
            else {
                token += ch;
            }
        }
    }
    else {
        while(inputFile.get(ch)) {
            if(ch == '\n') {
                throw std::runtime_error("Incorrect form of condition");
            }
            if (ch == ' ') {
                if (isNumber(token)) {

                    numbers_.push(std::stoi(token));
                    token.clear();
                }
                else if (pFactory->isRegist3red(token)) {
                    Command *pCommand = pFactory->createProductByName(token);

                    try {
                        pCommand->Execute(numbers_, inputFile);
                    } catch (std::underflow_error const &ex) {
                        std::cout << ex.what() << std::endl;
                        return;
                    } catch (std::runtime_error const &ex) {
                        std::cout << ex.what();
                        return;
                    }
                    token.clear();
                }
                else if(token == "else") {
                    token.clear();
                    while(inputFile.get(ch)) {
                        if (ch == '\n') {
                            throw std::runtime_error("Incorrect form of condition");
                        }

                        if (ch == ' ') {
                            if (isNumber(token)) {
                                token.clear();
                            }
                            else if (pFactory->isRegist3red(token)) {
                                token.clear();
                            }
                            else if(token == "then") {
                                std::cout << token << " ";
                                inputFile >> token;
                                if(token == ";") {
                                    std::cout << token << " ";
                                    return;
                                }
                                else {
                                    throw std::runtime_error("There is no ; at the end of the condition");
                                }
                            }
                        }
                        else {
                            token += ch;
                        }
                    }
                }
                else if(token == "then") {

                    inputFile >> token;
                    if(token == ";") {
                        return;
                    }
                    else {
                        throw std::runtime_error("There is no ; at the end of the condition");
                    }
                }
                else if(!token.empty()) {
                    token += "?";
                    throw std::runtime_error(token);
                }
            }
            else {
                token += ch;
            }
        }
    }
    throw std::runtime_error("Incorrect form of condition");
}

bool If::isNumber(const std::string& str) {
    if(str.empty()) {
        return false;
    }

    if(!std::isdigit(str[0]) && str[0] != '-' && str.length() == 1) {
        return false;
    }

    for(size_t i = 1; i < str.length(); ++i) {
        if(!std::isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

namespace {
    FactoryInitializer<If> Registration("if");
}