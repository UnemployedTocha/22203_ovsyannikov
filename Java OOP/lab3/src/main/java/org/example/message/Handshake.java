package org.example.message;

import org.example.util.PeerId;

import java.nio.ByteBuffer;
import java.util.Arrays;

public class Handshake {
    public static ByteBuffer Get(byte[] infoHash, byte[] peerId) {
        String protocol = "BitTorrent protocol";
        ByteBuffer buffer = ByteBuffer.allocate(68);
        buffer.put((byte)(protocol.length()));
        buffer.put(protocol.getBytes());
        for(int i = 0; i < 8; ++i) {
            buffer.put((byte)0);
        }
        buffer.put(infoHash);
        buffer.put(peerId);
        buffer.flip();
        return buffer;
    }

    static public byte[] GetInfoHash(byte[] message) {
        byte[] currInfoHash = new byte[20];
        ByteBuffer buffer = ByteBuffer.wrap(message);
        buffer.get(28, currInfoHash, 0, 20);
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
        return (Arrays.equals(hsProtocol, "BitTorrent protocol".getBytes()))
                && (Arrays.equals(protocolExtends, new byte[]{0, 0, 0, 0, 0, 0, 0, 0}));
    }

}
