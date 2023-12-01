#include "Interpreter.h"

int main() {
    Interpreter H;
    std::ifstream inputFile;

    try {
        inputFile.open("Prog.txt");
    } catch(const std::ifstream::failure& ex) {
        std::cout << "Exception opening/reading file";
    }

    H.TextProccesing(inputFile);

    inputFile.close();
    return 0;
}