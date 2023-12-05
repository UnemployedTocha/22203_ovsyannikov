#include "Interpreter.h"
#include <iostream>

int main() {
    Interpreter H;
    std::ifstream inputFile;
    std::string output;

    try {
        inputFile.open("Prog.txt");
    } catch(const std::ifstream::failure& ex) {
        std::cout << ex.what();
    }

    H.TextProccesing(inputFile, output);
    std::cout << output;
    inputFile.close();
    return 0;
}