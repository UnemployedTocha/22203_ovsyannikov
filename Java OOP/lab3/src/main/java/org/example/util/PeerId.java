package org.example.util;

public class PeerId {
    static public byte[] Calc(int port) {
        String str = Integer.toString(port);
        byte[] peerId = new byte[20];
        for(int i = 0; i < 20; ++i) {
            peerId[i] = (byte)str.charAt(i % str.length());
        }
        return peerId;
    }
 }
