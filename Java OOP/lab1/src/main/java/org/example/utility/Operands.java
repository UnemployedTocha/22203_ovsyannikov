package org.example.utility;

import java.util.Stack;

public class Operands {
    public int GetAndPop() {
        if(operands.empty()) {
            throw new RuntimeException("Incorrect operation that requires a number");
        }
        return operands.pop();
    }

    public int Top() {
        if(operands.empty()) {
            throw new RuntimeException("Incorrect operation that requires a number");
        }
        return operands.peek();
    }
    public void Push(Integer number) {
        operands.push(number);
    }

    public boolean IsEmpty() { return operands.empty(); }
    private final Stack<Integer> operands = new Stack<>();
}