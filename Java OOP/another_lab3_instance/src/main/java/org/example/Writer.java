package org.example;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;

public class Writer {
    private final int buffer_size = 1024;
    private ByteBuffer buffer = ByteBuffer.allocate(buffer_size);

}
