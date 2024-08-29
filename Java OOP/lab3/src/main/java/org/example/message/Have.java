package org.example.message;

import java.io.IOException;
import java.nio.ByteBuffer;

public class Have {
    public static ByteBuffer Get(int index) throws IOException {
        ByteBuffer buffer = ByteBuffer.allocate(4 + 1 + 4);
        buffer.putInt(5);
        buffer.put(MessageClassifier.GetMessageId(MessageType.Have));
        buffer.putInt(index);
        buffer.flip();
        return buffer;
    }
}
