#pragma once

#include <string>
#include "Tokens.h"

class Reader {
public:
    Reader(std::istream& inputFile);
    bool SplitStringToTokens(Tokens& tokens);
private:
    std::istream* inputFile_;
};