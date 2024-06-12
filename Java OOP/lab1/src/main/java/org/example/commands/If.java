package org.example.commands;

import org.example.utility.Operands;

import org.example.factory.Factory;
import org.example.utility.Utility;

import java.util.StringTokenizer;

public class If implements Command{
    @Override
    public void Execute(StringTokenizer tokens, Operands operands) {
        Factory factory = Factory.getInstance();
        Utility utility = new Utility();
        int num = operands.Top();
        if(num == 0) {
            while(tokens.hasMoreTokens()) {
                String token = tokens.nextToken();
                if(factory.isRegistered(token)) {
                    Command command = factory.createCommand(token);
                    command.Check(tokens, operands);
                } else if(token.equals("else")) {
                    while(tokens.hasMoreTokens()) {
                        token = tokens.nextToken();
                        if(utility.isNumber(token)) {
                            operands.Push(Integer.parseInt(token));
                        } else if(factory.isRegistered(token)) {
                            Command command = factory.createCommand(token);
                            command.Execute(tokens, operands);
                        } else if(token.equals("else")) {
                            throw new RuntimeException("Incorrect number of \"else\"");
                        } else if(token.equals("then")) {
                            utility.CheckSemiColumn(tokens);
                            return;
                        } else {
                            throw new RuntimeException(token + " ?");
                        }
                    }
                } else if(token.equals("then")) {
                    utility.CheckSemiColumn(tokens);
                    return;
                } else if(!utility.isNumber(token)) {
                    throw new RuntimeException(token + " ?");
                }
            }
        }
        else {
            while(tokens.hasMoreTokens()) {
                String token = tokens.nextToken();
                if(utility.isNumber(token)) {
                    operands.Push(Integer.parseInt(token));
                } else if(factory.isRegistered(token)) {
                    Command command = factory.createCommand(token);
                    command.Execute(tokens, operands);
                } else if(token.equals("else")) {
                    while(tokens.hasMoreTokens()) {
                        token = tokens.nextToken();
                        if(factory.isRegistered(token)) {
                            Command command = factory.createCommand(token);
                            command.Check(tokens, operands);
                        } else if(token.equals("else")) {
                            throw new RuntimeException("Incorrect number of \"else\"");
                        } else if(token.equals("then")) {
                            utility.CheckSemiColumn(tokens);
                            return;
                        } else if(!utility.isNumber(token)) {
                            throw new RuntimeException(token + " ?");
                        }
                    }
                } else if(token.equals("then")) {
                    utility.CheckSemiColumn(tokens);
                    return;
                } else {
                    throw new RuntimeException(token + " ?");
                }
            }
        }
    }

    @Override
    public void Check(StringTokenizer tokens, Operands operands) {
        Factory factory = Factory.getInstance();
        Utility utility = new Utility();
        int num = operands.Top();
        while(tokens.hasMoreTokens()) {
            String token = tokens.nextToken();
            if(factory.isRegistered(token)) {
                Command command = factory.createCommand(token);
                command.Check(tokens, operands);
            } else if(token.equals("else")) {
                while(tokens.hasMoreTokens()) {
                    token = tokens.nextToken();
                    if(factory.isRegistered(token)) {
                        Command command = factory.createCommand(token);
                        command.Check(tokens, operands);
                    } else if(token.equals("else")) {
                        throw new RuntimeException("Incorrect number of \"else\"");
                    } else if(token.equals("then")) {
                        utility.CheckSemiColumn(tokens);
                        return;
                    } else if(!utility.isNumber(token)) {
                        throw new RuntimeException(token + " ?");
                    }
                }
            } else if(token.equals("then")) {
                utility.CheckSemiColumn(tokens);
                return;
            } else if(!utility.isNumber(token)) {
                throw new RuntimeException(token + " ?");
            }
        }
        throw new RuntimeException("Incorrect form of condition");
    }

}
