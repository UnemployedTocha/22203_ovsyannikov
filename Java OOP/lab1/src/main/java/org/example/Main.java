package org.example;

import org.example.interpreter.Interpreter;


public class Main {

    public static void main(String[] args) {

        Interpreter i = new Interpreter();
        String in = "10 0 do i . loop ;\"";
        try {
            i.ProcessText(in);
        } catch(Exception ex) {
            System.out.println(ex.getMessage());
        }
    }
}