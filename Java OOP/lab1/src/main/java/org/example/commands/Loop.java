package org.example.commands;

import org.example.utility.Operands;
import org.example.factory.Factory;
import org.example.utility.Utility;

import java.util.StringTokenizer;

public class Loop implements Command{
    @Override
    public void Execute(StringTokenizer tokens, Operands operands) {
        Factory factory = Factory.getInstance();
        Utility utility = new Utility();

        int num1 = operands.GetAndPop();
        int num2 = operands.GetAndPop();

        String stringToLoop = GetStringToLoop(tokens);
        for(int i = num1; i < num2; ++i) {
            StringTokenizer tokensToLoop = new StringTokenizer(stringToLoop, " ");
            while(tokensToLoop.hasMoreElements()) {
                String token = tokensToLoop.nextToken();
                if(utility.isNumber(token)) {
                    operands.Push(Integer.parseInt(token));
                } else if(token.equals("i")) {
                    operands.Push(i);
                } else {
                    Command command = factory.createCommand(token);
                    command.Execute(tokens, operands);
                }
            }
        }
    }

    @Override
    public void Check(StringTokenizer tokens, Operands operands) {
        Factory factory = Factory.getInstance();

        int num1 = operands.GetAndPop();
        int num2 = operands.GetAndPop();

        String stringToLoop = GetStringToLoop(tokens);
        for(int i = num1; i < num2; ++i) {
            StringTokenizer tokensToLoop = new StringTokenizer(stringToLoop, " ");
            while(tokensToLoop.hasMoreElements()) {
                String token = tokensToLoop.nextToken();
                if(factory.isRegistered(token)){
                    Command command = factory.createCommand(token);
                    command.Check(tokens, operands);
                }
            }
        }
    }

    private String GetStringToLoop(StringTokenizer tokens) {
        Factory factory = Factory.getInstance();
        Utility utility = new Utility();
        String stringToLoop = "";
        while(tokens.hasMoreTokens()) {
            String token = tokens.nextToken();
            if(utility.isNumber(token) || factory.isRegistered(token) || token.equals("i")) {
                stringToLoop += token + " ";
            } else if(token.equals("loop")) {
                utility.CheckSemiColumn(tokens);
                return stringToLoop;
            }
            else {
                throw  new RuntimeException(token + " ?");
            }
        }
        throw new RuntimeException("There is no loop ; at the end of do");
    }
}
