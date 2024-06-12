package org.example.commands;

import org.example.utility.Operands;
import org.example.utility.Utility;

import java.util.StringTokenizer;

public class StringOutput implements Command{
    @Override
    public void Execute(StringTokenizer tokens, Operands operands) {
        if (!tokens.hasMoreTokens()) {
            throw new RuntimeException("There is no string to output");
        }
        Utility utility = new Utility();
        String token = tokens.nextToken();
        utility.CheckString(token);
        System.out.print(token.substring(0, token.length() - 2));
    }

    @Override
    public void Check(StringTokenizer tokens, Operands operands) {
        String token = tokens.nextToken();
        Utility utility = new Utility();
        utility.CheckString(token);
    }
}