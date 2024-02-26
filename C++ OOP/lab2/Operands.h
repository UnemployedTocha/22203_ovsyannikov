#pragma once

#include <stack>

class Operands {
public:
    int GetAndPop();
    void Push(int operand);
    int Top();
private:
    std::stack<int> operands_;
};