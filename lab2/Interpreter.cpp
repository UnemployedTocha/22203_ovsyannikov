#include "Interpreter.h"
#include <iostream>
#include "Reader.h"
#include "Tokens.h"

void Interpreter::TextProccesing(std::ifstream& inputFile) {
    Reader reader(inputFile);
    Tokens tokens;

    std::string token;
    Factory<Command, std::string, Command*(*)()>* pFactory = Factory<Command, std::string, Command*(*)()>::getInstance();
    while(reader.SplitStringToTokens(tokens)) {
        while (!tokens.IsEmpty()) {
            token = tokens.GetAndPop();
            if (isNumber(token)) {
                operands_.push(std::stoi(token));
            }
            else if (pFactory->isRegist3red(token)) {
                Command *pCommand = pFactory->createProductByName(token);
                try {
                    pCommand->Execute(operands_, tokens, output_, reader);
                } catch (std::underflow_error const &ex) {
                    std::cout << ex.what() << std::endl;
                    return;
                } catch (std::runtime_error const &ex) {
                    std::cout << ex.what();
                    return;
                }
            }
            else if (!token.empty()) {
                std::cout << token << " ?";
                return;
            }

        }
    }
    std::cout << output_;
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