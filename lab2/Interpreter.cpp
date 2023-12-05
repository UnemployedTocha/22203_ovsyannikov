#include "Interpreter.h"
#include <iostream>
#include "Reader.h"
#include "Tokens.h"
#include "Utility.h"
#include <memory>

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
                auto pCommand = std::unique_ptr<Command>(pFactory->createProductByName(token));
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
}
