package org.example;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.Iterator;
import java.util.Set;

public class Server {
    private Logger logger;
    private int port;
    private ServerSocketChannel serverSocketChannel;


    public Server(int port) {
        logger = LogManager.getLogger(Server.class);
        this.port = port;
    }

    void StartServer() throws IOException {
        Selector selector = Selector.open();
        serverSocketChannel = ServerSocketChannel.open();

        serverSocketChannel.bind(new InetSocketAddress(port));
        serverSocketChannel.configureBlocking(false);

        serverSocketChannel.register(selector, SelectionKey.OP_ACCEPT);
        System.out.println("Server is listening on port " + port);

        while(true) {
            selector.select();
            Set<SelectionKey> selectedKeys = selector.selectedKeys();
            Iterator<SelectionKey> it = selectedKeys.iterator();

            while(it.hasNext()) {
                SelectionKey key = it.next();
                it.remove();

//                if(!key.isValid()) {
//                    continue;
//                }
                if(key.isAcceptable()) {
                    AcceptConnection(selector, serverSocketChannel);
                } else if(key.isReadable()) {
                    HandleRead(key);
                } else if(key.isWritable()) {
                    HandleWrite(key);
                }

            }
        }

    }
    private void AcceptConnection(Selector selector, ServerSocketChannel serverSocketChannel) throws IOException {
        SocketChannel client = serverSocketChannel.accept();
        client.configureBlocking(false);
        client.register(selector, SelectionKey.OP_READ);
        logger.info("Client connected");
    }
    private void HandleRead(SelectionKey key) throws IOException {
        SocketChannel client = (SocketChannel)key.channel();
        String message = Reader.ReadMessageAsString(client);
        System.out.println("CLIENT MESSAGE: " + message);

        byte[] response = ("Message received: "  + message).getBytes();
        ByteBuffer buffer = ByteBuffer.allocate(4 + response.length);
        buffer.putInt(response.length);
        buffer.put(response);
        buffer.flip();
        client.write(buffer);

//        key.interestOps(SelectionKey.OP_WRITE);
    }

    private void HandleWrite(SelectionKey key) throws IOException {
        System.out.println("Server connection is closed");
        SocketChannel client = (SocketChannel) key.channel();
        client.close();
        key.cancel();
    }

    private File GetFile(String fileName) {
        return new File("./server_files/" + fileName);
    }

    public static void main(String[] args) throws IOException {
        Server server = new Server(8000);
        server.StartServer();
    }
}
