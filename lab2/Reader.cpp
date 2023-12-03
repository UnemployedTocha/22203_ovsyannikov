#include "Reader.h"
#include <sstream>
Reader::Reader(std::istream& inputFile) : inputFile_(&inputFile){}

bool Reader::SplitStringToTokens(Tokens& tokens) {
    std::string str;
    std::string token;
    bool isRead = false;
    if(std::getline(*inputFile_, str)) {
        std::stringstream ss(str);
        while (ss >> token) {
            tokens.Push(token);
        }
        isRead = true;
    }
    return isRead;
}