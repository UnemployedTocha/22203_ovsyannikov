package org.example;

import java.io.*;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.Iterator;
import java.util.Set;
import java.util.logging.*;

public class FileServer {
    private static final org.apache.logging.log4j.Logger log = org.apache.logging.log4j.LogManager.getLogger(FileServer.class);
    private final int BUFFER_SIZE = 4096;
    private final int port = 8000;
    private final ByteBuffer byteBuffer = ByteBuffer.allocate(BUFFER_SIZE);
    private static final Logger logger = Logger.getLogger(FileServer.class.getName());



    public FileServer(){}

    public void StartServer() throws IOException {
        Selector selector = Selector.open();
        ServerSocketChannel serverSocketChannel = ServerSocketChannel.open();

        serverSocketChannel.bind(new InetSocketAddress(port));
        serverSocketChannel.configureBlocking(false);

        serverSocketChannel.register(selector, SelectionKey.OP_ACCEPT);
        System.out.println("Server is listening on port " + port);

        Listen(selector, serverSocketChannel);
    }

    private void Listen(Selector selector, ServerSocketChannel serverSocketChannel) throws IOException{
        while(true) {
            selector.select();
            Set<SelectionKey> selectionKeys = selector.selectedKeys();
            Iterator<SelectionKey> it = selectionKeys.iterator();

            while(it.hasNext()) {
                SelectionKey key = it.next();
                it.remove();
                HandleKey(key, selector, serverSocketChannel);
            }
        }
    }
    private void HandleKey(SelectionKey key, Selector selector, ServerSocketChannel serverSocketChannel) throws IOException {
        if(key.isAcceptable()) {
            AcceptConnection(serverSocketChannel, selector);
        } else if(key.isReadable()) {
            HandleRead(key);
        }
    }
    private void AcceptConnection(ServerSocketChannel serverSocketChannel, Selector selector) throws IOException{
        SocketChannel client = serverSocketChannel.accept();
        logger.info("Client connected: " + client.getRemoteAddress() + ":" + client.getLocalAddress());
        client.configureBlocking(false);
        client.register(selector, SelectionKey.OP_READ);
    }
    private void HandleRead(SelectionKey key) throws IOException {
        SocketChannel client = (SocketChannel)key.channel();
        byteBuffer.clear();

        int bytesRead = client.read(byteBuffer);
        if(bytesRead == -1) {
            client.close();
            key.cancel();
            return;
        }
        byteBuffer.flip();
        BufferedReader reader = new BufferedReader(new InputStreamReader(new ByteArrayInputStream(byteBuffer.array(), 0, bytesRead)));
        String line = reader.readLine();

        switch(line) {
            case null:
                logger.info("Error communication with clinet");
                client.close();
                key.cancel();
                break;
            case "LIST":
                ListFiles(client);
                break;
            case "UPLOAD":
                UploadFile(client, reader);
                break;
            case "DOWNLOAD":
                DownloadFile(client, reader);
                break;
            default:
                SendMessage(client, "Unknown command\n");
        }
    }
    private void ListFiles(SocketChannel client) throws IOException {
        System.out.println("Trying to list files: ./server_files/");
        File dir = new File("./server_files/");
        File[] files = dir.listFiles();
        StringBuilder response = new StringBuilder();
//        System.out.println(dir.getAbsolutePath());
        if(files != null) {
            for (File file : files) {
                response.append(file.getName()).append("\n");
            }
            response.append("END").append("\n");
        } else {
            response.append("There is no files on server\n");
        }
        SendMessage(client, response.toString());
    }

    private void DownloadFile(SocketChannel client, BufferedReader reader) throws IOException {
        String fileName = reader.readLine();
        File file = new File("./server_files/" + fileName);
        if(file.exists()) {
            try(FileInputStream fileIn = new FileInputStream(file);
                BufferedInputStream in = new BufferedInputStream(fileIn)) {
                byteBuffer.clear();

                int bytesRead;
                while((bytesRead = in.read(byteBuffer.array())) != -1) {
                    byteBuffer.limit(bytesRead);
                    client.write(byteBuffer);
                    byteBuffer.clear();
                }

                logger.info("File downloaded: " + file.getName());
            }
        } else {
            logger.info("There is no requested file: \" + fileName");
            SendMessage(client, "There is no such file: " + fileName);
        }
    }
    private void UploadFile(SocketChannel client, BufferedReader reader) throws IOException {
        String fileName = reader.readLine();
        File file = new File("./server_files/" + fileName);
        try(FileOutputStream fileOut = new FileOutputStream(file);
            BufferedOutputStream out = new BufferedOutputStream(fileOut)) {
            byteBuffer.clear();
            int bytesRead;
            while((bytesRead = client.read(byteBuffer)) > 0) {
                byteBuffer.flip();
                out.write(byteBuffer.array(), 0, bytesRead);
                byteBuffer.clear();
            }
            logger.info("File uploaded: " + fileName);
        }
    }

        private void SendMessage(SocketChannel client, String message) throws IOException {
        byteBuffer.clear();
        byteBuffer.put(message.getBytes());
        byteBuffer.flip();
        client.write(byteBuffer);
    }

    private void listFiles(PrintWriter writer) {
        System.out.println("Trying to list files: ./server_files/");
        File dir = new File("./server_files/");
        File[] files = dir.listFiles();
//        System.out.println(dir.getAbsolutePath());
        if(files != null) {
            for (File file : files) {
                writer.println(file.getName());
            }
        } else {
            writer.println("No files found.");
        }
        writer.println("END");
    }

    public static void main(String[] args) {
        try {
            FileServer server = new FileServer();
            server.StartServer();
        } catch (Exception ex) {
            logger.info("Failed to start server: " + ex.getMessage());
        }
    }
}