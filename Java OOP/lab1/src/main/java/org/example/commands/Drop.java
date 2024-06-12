package org.example.commands;

import org.example.utility.Operands;

import java.util.StringTokenizer;

public class Drop implements Command{
    @Override
    public void Execute(StringTokenizer tokens, Operands operands) {
        operands.GetAndPop();
    }

    @Override
    public void Check(StringTokenizer tokens, Operands operands) {

    }

}