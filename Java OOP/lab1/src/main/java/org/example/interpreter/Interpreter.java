package org.example.interpreter;

import org.example.commands.Command;
import org.example.factory.Factory;
import org.example.utility.Operands;
import org.example.utility.Utility;

import java.util.*;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;


public class Interpreter {
    public void ProcessText(String in) {
//        Logger logger = LogManager
        Factory f = Factory.getInstance();

        try(Scanner scanner = new Scanner(in)) {
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                StringTokenizer tokens = new StringTokenizer(line, " ");
                while (tokens.hasMoreTokens()) {
                    String s = tokens.nextToken();
                    if (utility.isNumber(s)) {
                        operands.Push(Integer.parseInt(s));
                    } else if (f.isRegistered(s)) {
                        Command command = f.createCommand(s);
                        command.Execute(tokens, operands);
                    } else {
                        throw new RuntimeException(s + " ?");
                    }
                }
            }
        }
    }

    private final Operands operands = new Operands();
    private final Utility utility = new Utility();
}
