package org.example;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Set;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.example.message.Bitfield;
import org.example.message.Handshake;
import org.example.message.MessageType;
import org.example.message.PieceManager;

public class Server implements Runnable{
    Logger logger;
    Parser parser;
    PieceManager pieceManager;
    Selector selector;
    ServerSocketChannel serverSocketChannel;
    private final String ip;
    Bitfield bitfield;
    private final int port;

    public Server(String ip, int port, Bitfield bitfield, Parser parser, PieceManager pieceManager, String filePath) {
        logger = LogManager.getLogger(Server.class);
        this.bitfield = bitfield;
        this.ip = ip;
        this.port = port;
        this.parser = parser;
        this.pieceManager = pieceManager;

    }

    @Override
    public void run() {
        logger.info("Running server at port: " + port);
        try {
            selector = Selector.open();
            serverSocketChannel = ServerSocketChannel.open();
            serverSocketChannel.bind(new InetSocketAddress(ip, port));
            serverSocketChannel.configureBlocking(false);
            serverSocketChannel.register(selector, SelectionKey.OP_ACCEPT);

            while(true) {
                selector.select();
                Set<SelectionKey> keys = selector.selectedKeys();
                Iterator<SelectionKey> it = keys.iterator();

                while(it.hasNext()) {
                    SelectionKey key = it.next();
                    it.remove();

                    if(key.isValid() && key.isAcceptable()) {
                        HadnleConnection();
                    }
                    if(key.isValid() && key.isReadable()) {
                        HandleRead(key);
                    }
                }
            }

        } catch (IOException ex) {
            logger.error(ex.getMessage());
        }
        logger.info("Server stopped");
    }

    void HadnleConnection() throws IOException {
        SocketChannel client = serverSocketChannel.accept();
        client.configureBlocking(false);
        client.register(selector, SelectionKey.OP_READ, serverSocketChannel);
    }
    private void HandleRead(SelectionKey key) throws IOException{
        SocketChannel socketChannel = (SocketChannel)key.channel();
        try {
            ByteBuffer message = ByteBuffer.wrap(ReadMessage(socketChannel));
            if(Handshake.IsHandshakeMessage(message.array())) {
                Handshake hs = new Handshake(parser.GetInfoHash());
                ByteBuffer buffer = ByteBuffer.wrap(hs.GetHandshakeMessage());
                while(buffer.hasRemaining()) {
                    socketChannel.write(buffer);
                }
                logger.info("Handshake message received, sending handshake back!");
            } else {
                byte type = message.get();
                if(PieceManager.GetMessageType(type) == MessageType.Bitfield) {
                    ByteBuffer bitfieldMessage = ByteBuffer.wrap(bitfield.GetBitfieldMessage());
                    while(bitfieldMessage.hasRemaining()) {
                        socketChannel.write(bitfieldMessage);
                    }
                    logger.info("Bitfield message received! sending handshake back!");
                } else if(PieceManager.GetMessageType(type) == MessageType.Request) {
                    int index = message.getInt();
                    int begin = message.getInt();
                    int pieceSize = message.getInt();

                    if(bitfield.PieceExists(index)) {
                        byte[] piece = pieceManager.GetFilePiece(index);
                        if(!Arrays.equals(PieceManager.CalcPieceHash(piece), parser.GetTorrentPieceHash(index))) {
                            logger.info("SERVER SENDS NOT CORRECT PIECE: {}", index);
                        }
                        ByteBuffer pieceMessage = ByteBuffer.allocate(4 + 1 + 4 + 4 + piece.length);
                        pieceMessage.putInt(1 + 4 + 4 + piece.length);
                        pieceMessage.put(PieceManager.GetMessageId(MessageType.Piece));
                        pieceMessage.putInt(index);
                        pieceMessage.putInt(begin);
                        pieceMessage.put(piece);
                        pieceMessage.flip();

                        while(pieceMessage.hasRemaining()) {
                            socketChannel.write(pieceMessage);
                        }
                        logger.info("Request message received and piece {} sent back!", index);
                    } else {
                        logger.info("REQUESTABLE PIECE DOES NOT EXIST");
                    }
                } else {
                    logger.info("Unknown request");
                }
            }
        } catch (IOException ex) {
            key.cancel();
            key.channel().close();
        }
    }

    private byte[] ReadMessage(SocketChannel socketChannel) throws IOException {
        ByteBuffer tempBuffer = ByteBuffer.allocate(1);
        while(tempBuffer.hasRemaining()) {
            socketChannel.read(tempBuffer);
        }
        tempBuffer.flip();
        byte len = tempBuffer.get();
        ByteBuffer buffer;

        if(len == 19) {
            logger.info("READING PROVIDED CHECKING HANDSHAKE!!!!!");
            buffer = ByteBuffer.allocate(68);
            buffer.put(len);
            while (buffer.hasRemaining()) {
                int bytesRead = socketChannel.read(buffer);
                if (bytesRead == -1) {
                    throw new IOException();
                }
            }
        } else {
            ByteBuffer lenBuffer = ByteBuffer.allocate(4);
            lenBuffer.put(len);
            while (lenBuffer.hasRemaining()) {
                int bytesRead = socketChannel.read(lenBuffer);
                if (bytesRead == -1) {
                    throw new IOException();
                }
            }
            lenBuffer.flip();
            int length = lenBuffer.getInt();
            buffer = ByteBuffer.allocate(length);
            while (buffer.hasRemaining()) {
                int bytesRead = socketChannel.read(buffer);
                if (bytesRead == -1) {
                    throw new IOException();
                }
            }
        }
        return buffer.array();
    }
}
