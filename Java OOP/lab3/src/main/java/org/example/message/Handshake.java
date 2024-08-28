package org.example.message;

import java.nio.ByteBuffer;
import java.util.Arrays;

public class Handshake {
    private String protocol = "BitTorrent protocol";
    private byte[] infoHash;
    private byte[] message;
    public Handshake(byte[] infoHash, int port) {
        this.infoHash = infoHash;
        ByteBuffer buffer = ByteBuffer.allocate(68);
        buffer.put((byte)protocol.length());
        buffer.put(protocol.getBytes());
        buffer.put(new byte[]{0, 0, 0, 0, 0, 0, 0, 0});
        buffer.put(infoHash);
        buffer.put(GetPeerId(port));
        message = buffer.array();
    }
    public byte[] GetInfoHash() {
        return infoHash;
    }
    static public byte[] GetInfoHash(byte[] message) {
        byte[] currInfoHash = new byte[20];
        ByteBuffer buffer = ByteBuffer.wrap(message);
        buffer.get(28, currInfoHash, 0, 20);
        System.out.println();
        return currInfoHash;
    }
    static public boolean IsHandshakeMessage(byte[] msg) {
        if(msg.length != 68) {
            return false;
        }
        ByteBuffer buffer = ByteBuffer.wrap(msg);
        byte protocolLen = buffer.get(0);
        byte[] hsProtocol = new byte[19];
        buffer.get(1, hsProtocol, 0, 19);
        byte[] protocolExtends = new byte[8];
        buffer.get(20, protocolExtends, 0, 8);
        return (protocolLen == 19)
                && (Arrays.equals(hsProtocol, "BitTorrent protocol".getBytes()))
                && (Arrays.equals(protocolExtends, new byte[]{0, 0, 0, 0, 0, 0, 0, 0}));
    }
    static public byte[] GetPeerId(int port) {
        byte[] peerId = new byte[20];
        String portString = Integer.toString(port);
        for(int i = 0; i < 20; ++i) {
            peerId[i] = (byte)portString.charAt(i % portString.length());
            System.out.print((char)peerId[i]);
        }
        System.out.println(" ");
        return peerId;
    }
    public byte[] GetHandshakeMessage() {
        return message;
    }
    public void Debug() {
        System.out.println(Arrays.toString(message));
    }

}
