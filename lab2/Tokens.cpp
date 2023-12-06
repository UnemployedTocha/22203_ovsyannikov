#include "Tokens.h"

Tokens::Tokens() = default;

Tokens::Tokens(const Tokens& t) {
    tokens_ = t.tokens_;
}
void Tokens::Push(const std::string& s) {
    tokens_.push(s);
}

std::string Tokens::GetAndPop() {
    std::string s = tokens_.front();
    tokens_.pop();
    return s;
}

bool Tokens::IsEmpty() {
    return tokens_.empty();
}