package org.example.utility;

import java.util.StringTokenizer;

public class Utility {
    public Utility() { }

    public boolean isNumber(String str) {
        if(str.isEmpty()) {
            return false;
        }
        if(str.charAt(0) == '-' && str.length() == 1) {
            return false;
        }
        if(str.charAt(0) > '9'|| str.charAt(0) < '0') {
            return false;
        }
        for(int i = 1; i < str.length(); ++i) {
            if(str.charAt(i) > '9'|| str.charAt(i) < '0') {
                return false;
            }
        }
        return true;
    }

    public boolean CheckSemiColumn(StringTokenizer tokens) {
        return tokens.hasMoreTokens() && tokens.nextToken().equals(";");
    }
    public void CheckString(String token) {
        if (token.charAt(token.length() - 1) != '"') {
            throw new RuntimeException("Incorrect form of String");
        }
    }
}
