package org.example.commands;

import org.example.utility.Operands;

import java.util.StringTokenizer;

public class Equality implements Command{
    @Override
    public void Execute(StringTokenizer tokens, Operands operands) {
        int num1 = operands.GetAndPop();
        int num2 = operands.GetAndPop();
        if (num1 == num2) {
            operands.Push(1);
        } else {
            operands.Push(0);
        }
    }

    @Override
    public void Check(StringTokenizer tokens, Operands operands) {

    }

}

