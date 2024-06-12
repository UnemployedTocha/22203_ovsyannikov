package org.example.commands;

import org.example.utility.Operands;

import java.util.StringTokenizer;

public interface Command {
    void Execute(StringTokenizer tokens, Operands operands);
    void Check(StringTokenizer tokens, Operands operands);
}
