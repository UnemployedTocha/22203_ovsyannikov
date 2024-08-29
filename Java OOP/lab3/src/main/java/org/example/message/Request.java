package org.example.message;

import java.nio.ByteBuffer;

public class Request {
    public static ByteBuffer Get(byte messageId, int index,int begin, int pieceSize) {
        ByteBuffer buffer = ByteBuffer.allocate(4 + 1 + 4 + 4 + 4);
        buffer.putInt(13);
        buffer.put(messageId);
        buffer.putInt(index);
        buffer.putInt(begin);
        buffer.putInt(pieceSize);
        buffer.flip();
        return buffer;
    }
}
