#include "Utility.h"
#include <stdexcept>

bool isNumber(const std::string& str) {
    if(str.empty()) {
        return false;
    }

    if(str.size() == 1  && str.front() == '-') {
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

void CheckSemicolon(Tokens& tokens) {
    if(tokens.IsEmpty()) {
        throw std::runtime_error("There is no ; at the end of condition");
    }
    std::string token = tokens.GetAndPop();
    if(token != ";") {
        throw std::runtime_error("There is no ; at the end of condition");
    }
}