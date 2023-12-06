#include "Interpreter.h"
#include "Reader.h"
#include "Tokens.h"
#include "Utility.h"
#include <memory>
#include "Factory.h"

void Interpreter::TextProccesing(std::istream& inputFile, std::string& output){
    Reader reader(inputFile);
    Tokens tokens;
    Operands operands;

    std::string token;
    auto pFactory = Factory<Command, std::string, Command*(*)()>::getInstance();
    while(reader.SplitStringToTokens(tokens)) {
        while (!tokens.IsEmpty()) {
            token = tokens.GetAndPop();
            if (isNumber(token)) {
                operands_.Push(std::stoi(token));

            }
            else if (pFactory->isRegist3red(token)) {
                auto pCommand = std::unique_ptr<Command>(pFactory->createProductByName(token));
                pCommand->Execute(operands_, tokens, output, reader);
            }
            else if (!token.empty()) {
                token += " ?";
                throw std::runtime_error(token);
            }
        }
    }

    if(!output.empty() && output.back() == ' ') {
        output.pop_back();
    }
}
