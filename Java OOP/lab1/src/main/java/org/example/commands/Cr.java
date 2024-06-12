package org.example.commands;

import org.example.utility.Operands;

import java.util.StringTokenizer;

public class Cr implements Command{
    @Override
    public void Execute(StringTokenizer tokens, Operands operands) {
        System.out.print('\n');
    }

    @Override
    public void Check(StringTokenizer tokens, Operands operands) {

    }

}