package org.example;

import org.apache.logging.log4j.Logger;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.lang.reflect.Array;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;
import java.nio.charset.StandardCharsets;
import java.util.Arrays;

public class Reader {
    public static byte[] ReadBytes(SocketChannel socketChannel, int bytesNum) throws IOException {
        ByteBuffer buffer = ByteBuffer.allocate(bytesNum);
        int bytesRead;
        if((bytesRead = socketChannel.read(buffer)) == -1) {
            throw new IOException("Socket close");
        }
        return buffer.array();
    }
    public static byte[] ReadMessageInBytes(SocketChannel socketChannel) throws IOException {
        int length = ByteBuffer.wrap(ReadBytes(socketChannel, 4), 0, 4).getInt(0);
        return ReadBytes(socketChannel, length);
    }

    public static String ReadMessageAsString(SocketChannel socketChannel) throws IOException {
        return new String(ReadMessageInBytes(socketChannel), StandardCharsets.UTF_8);
    }
}
