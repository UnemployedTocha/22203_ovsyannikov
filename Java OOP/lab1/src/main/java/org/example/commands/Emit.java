package org.example.commands;

import org.example.utility.Operands;

import java.util.StringTokenizer;

public class Emit implements Command{
    @Override
    public void Execute(StringTokenizer tokens, Operands operands) {
        int num1 = operands.GetAndPop();
        char ch = (char)num1;
        System.out.print(ch + " ");
    }

    @Override
    public void Check(StringTokenizer tokens, Operands operands) {

    }

}
