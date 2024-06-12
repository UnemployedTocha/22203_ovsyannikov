package org.example.commands;

import org.example.utility.Operands;
import java.util.StringTokenizer;

public class Dup implements Command{
    @Override
    public void Execute(StringTokenizer tokens, Operands operands) {
        int num1 = operands.Top();
        operands.Push(num1);
    }

    @Override
    public void Check(StringTokenizer tokens, Operands operands) {

    }

}