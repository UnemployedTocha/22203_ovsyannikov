#include "Interpreter.h"
#include <iostream>
#include <sstream>

int main() {
    Interpreter H;
    std::istringstream inputFile("0 if 4 5 + . then 40 50 + . then ;");
    std::string output;

//    try {
//        inputFile.open("Prog.txt");
//    } catch(const std::ifstream::failure& ex) {
//        std::cout << ex.what();
//    }

    H.TextProccesing(inputFile, output);

    std::cout << output;
//    inputFile.close();
    return 0;
}