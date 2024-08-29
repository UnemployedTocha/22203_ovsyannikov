package org.example.util;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class Hash {
    static public byte[] CalcPieceHash(byte[] piece) {
        MessageDigest messageDigest = null;
        try {
            messageDigest = MessageDigest.getInstance("SHA-1");
            messageDigest.update(piece);
        } catch (NoSuchAlgorithmException ex) {
            System.out.println(ex.getMessage());
        }

        assert messageDigest != null;
        return messageDigest.digest();
    }
}
