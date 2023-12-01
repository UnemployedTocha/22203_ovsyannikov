#include "Interpreter.h"
#include <iostream>

void Interpreter::TextProccesing(std::ifstream& inputFile) {
    std::string token;
    char ch;
    Factory<Command, std::string, Command*(*)()>* pFactory = Factory<Command, std::string, Command*(*)()>::getInstance();

    while(inputFile.get(ch)) {
        if(ch == ' ' || ch == '\n') {
            if (isNumber(token)) {
                operands_.push(std::stoi(token));
                std::cout << token << " ";
                token.clear();
            }
            else if (pFactory->isRegist3red(token)) {
                Command *pCommand = pFactory->createProductByName(token);
                try {
                    pCommand->Execute(operands_, inputFile);
                } catch (std::underflow_error const &ex) {
                    std::cout << ex.what() << std::endl;
                    return;
                } catch (std::runtime_error const &ex) {
                    std::cout << ex.what();
                    return;
                }
                std::cout << token << " ";
                token.clear();
            }
            else if (!token.empty()) {
                std::cout << token << " ?";
                return;
            }
            if (ch == '\n') {
                std::cout << "ok" << std::endl;
            }
        }
        else {
            token += ch;
        }
    }
    PrintStack();
}

void Interpreter::PrintStack() {
    std::stack<int> tempStack = operands_;

    if(!tempStack.empty()) {
        std::cout << "Top -> [ ";
    }
    while(!tempStack.empty()) {
        int x = tempStack.top();
        std::cout << x << " ";
        tempStack.pop();
    }
    std::cout << "]";
}


bool Interpreter::isNumber(const std::string& str) {
    if(str.empty()) {
        return false;
    }
    for(char ch : str) {
        if(!std::isdigit(ch)) {
            return false;
        }
    }
    return true;
}


/*
    while(std::getline(inputFile, program)) {
        program += " ";
        std::cout << program << " ";

        std::string token;
        for(char ch : program) {
            if(ch == ' ') {
                if(isNumber(token)) {
                    operands_.push(std::stoi(token));
                    token.clear();
                }
                else if(pFactory -> isRegist3red(token)) {
                    Command* pCommand = pFactory -> createProductByName(token);
                    try {
                        pCommand->Execute(operands_, program);
                    } catch(std::underflow_error const& ex) {
                        std::cout << ex.what() << std::endl;
                        return;
                    } catch(std::runtime_error const& ex) {
                        std::cout << ex.what();
                        return;
                    }
                    token.clear();
                }
                else if(!token.empty()){
                    std::cout << token << " ?";
                    return;
                }
            }
            else {
                token += ch;
            }
        }
        std::cout << "ok" << std::endl;
    }
    PrintStack();
 */