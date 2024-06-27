package org.example;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.Channel;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.SocketChannel;
import java.util.Iterator;
import java.util.Scanner;
import java.util.Set;

public class Client {
    SocketChannel client;
    private final int port;
    private final String serverAddress;
    Selector selector;


    public void StartDownload() throws IOException {
        selector = Selector.open();
        client = SocketChannel.open();
        client.configureBlocking(false);
        client.connect(new InetSocketAddress(serverAddress, port));
        client.register(selector, SelectionKey.OP_CONNECT);
        System.out.println("Connecting to the server");

        while(true) {
            selector.select();
            Set<SelectionKey> selectionKeys = selector.selectedKeys();
            Iterator<SelectionKey> it = selectionKeys.iterator();

            while(it.hasNext()) {
                SelectionKey key = it.next();
                it.remove();

                if(key.isConnectable()) {
                    HandleConnection(key);
                } else if(key.isReadable()) {
                    HandleRead(key);
                } else if(key.isWritable()) {
                    HandleWrite(key);
                }

            }
        }

    }

    private void HandleWrite(SelectionKey key) throws IOException {
        SocketChannel channel = (SocketChannel) key.channel();
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter message: ");
        String message = scanner.nextLine();

        byte[] messageBytes = message.getBytes();
        ByteBuffer buffer = ByteBuffer.allocate(4 + messageBytes.length);
        buffer.putInt(messageBytes.length);
        buffer.put(messageBytes);
        buffer.flip();
        channel.write(buffer);

        if (!buffer.hasRemaining()) {
            key.interestOps(SelectionKey.OP_READ);
        }
    }

    private void HandleRead(SelectionKey key) throws IOException {
        SocketChannel channel = (SocketChannel) key.channel();
//        ByteBuffer buffer = ByteBuffer.allocate(256);
//        int bytesRead = channel.read(buffer);
//
//        if (bytesRead == -1) {
//            channel.close();
//            key.cancel();
//            return;
//        }
//
//        buffer.flip();
//        byte[] data = new byte[bytesRead];
//        buffer.get(data);
//        String response = new String(data);
        String response = Reader.ReadMessageAsString(channel);
        System.out.println("Server response: " + response);

        key.interestOps(SelectionKey.OP_WRITE);
    }

    private void HandleConnection(SelectionKey key) throws IOException {
        SocketChannel server = (SocketChannel)key.channel();
        if(server.finishConnect()) {
            server.register(selector, SelectionKey.OP_WRITE);
            System.out.println("Successfully connected");
        }
    }


    public Client(String serverAddress , int port) throws IOException {
        this.port = port;
        this.serverAddress = serverAddress;
    }






    public static void main(String[] args) {
        String host = "127.0.0.1"; // Пример хоста
        int port = 8000; // Пример порта

        try {
            Client client = new Client(host, port);
            client.StartDownload();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
