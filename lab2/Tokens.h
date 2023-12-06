#pragma once

#include <queue>
#include <string>

class Tokens {
public:
    Tokens();
    Tokens(const Tokens& t);
    void Push(const std::string& s);
    std::string GetAndPop();
    bool IsEmpty();
private:
    std::queue<std::string> tokens_;
};