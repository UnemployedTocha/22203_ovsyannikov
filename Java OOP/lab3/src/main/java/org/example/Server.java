package org.example;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.*;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.example.message.*;
import org.example.util.Hash;
import org.example.util.Parser;
import org.example.util.PeerId;

public class Server implements Runnable{
    Logger logger;
    Parser parser;
    PieceManager pieceManager;
    Selector selector;
    ServerSocketChannel serverSocketChannel;
    private final String ip;
    Bitfield bitfield;
    private final int port;
    private final byte[] myPeerId;
    private final List<PeerInfo> peers;
    private HashMap<SocketChannel, PeerInfo> map;

    public Server(String ip, int port, Bitfield bitfield, Parser parser, PieceManager pieceManager, List<PeerInfo> peers) {
        logger = LogManager.getLogger(Server.class);
        this.bitfield = bitfield;
        this.ip = ip;
        this.port = port;
        this.parser = parser;
        this.pieceManager = pieceManager;
        this.myPeerId = PeerId.Calc(port);
        this.peers = peers;
        map = new HashMap<>();
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
        map.put(client, null);
    }
    private void HandleRead(SelectionKey key) throws IOException{
        SocketChannel socketChannel = (SocketChannel)key.channel();
        try {
            ByteBuffer message = ReadMessage(socketChannel);

            if(Handshake.IsHandshakeMessage(message.array())) {
                ByteBuffer buffer = Handshake.Get(parser.GetInfoHash(), myPeerId);
                while(buffer.hasRemaining()) {
                    socketChannel.write(buffer);
                }
                byte nineteen = message.get();
                byte[] protocol = new byte[19];
                message.get(protocol);
                byte[] protocolExtension = new byte[8];
                message.get(protocolExtension);
                byte[] infoHash = new byte[20];
                message.get(infoHash);
                byte[] clientPeerId = new byte[20];
                message.get(clientPeerId);

                System.out.println("In Server: "  + "peerId: " + Arrays.toString(clientPeerId) + "  myPeerId: " + Arrays.toString(myPeerId));
                map.put(socketChannel, FindPeerById(clientPeerId));
                logger.info("Handshake message received, sending handshake back!");
            } else {
                byte messageId = message.get();
                if(MessageClassifier.GetMessageType(messageId) == MessageType.Bitfield) {
                    ByteBuffer bitfieldMessage = ByteBuffer.wrap(bitfield.GetBitfieldMessage());
                    while(bitfieldMessage.hasRemaining()) {
                        socketChannel.write(bitfieldMessage);
                    }
                    logger.info("Bitfield message received! sending handshake back!");
                } else if(MessageClassifier.GetMessageType(messageId) == MessageType.Request) {
                    int index = message.getInt();
                    int begin = message.getInt();
                    int pieceSize = message.getInt();

                    if(bitfield.PieceExists(index)) {
                        byte[] piece = pieceManager.GetFilePiece(index);
                        if(!Arrays.equals(Hash.CalcPieceHash(piece), parser.GetTorrentPieceHash(index))) {
                            logger.error("SERVER SENDS NOT CORRECT PIECE: {}", index);
                        }
                        ByteBuffer pieceMessage = Piece.Get(piece, index, begin);
                        while(pieceMessage.hasRemaining()) {
                            socketChannel.write(pieceMessage);
                        }
                        logger.info("Request message received and piece {} sent back!", index);
                    } else {
                        logger.info("REQUESTABLE PIECE DOES NOT EXIST");
                    }
                } else if(MessageClassifier.GetMessageType(messageId) == MessageType.Have) {
                    if(map.get(socketChannel) == null || (map.get(socketChannel).GetBitfield()) == null) {
                        return;
                    }
                    int index = message.getInt();
                    map.get(socketChannel).GetBitfield().Set(index);
                  logger.info("Have message received, piece with index {} may be requested from peer {}", index, map.get(socketChannel).GetPort());
                } else {
                    logger.info("Unknown request");
                }
            }
        } catch (IOException ex) {
            key.cancel();
            key.channel().close();
        }
    }

    private ByteBuffer ReadMessage(SocketChannel socketChannel) throws IOException {
        ByteBuffer tempBuffer = ByteBuffer.allocate(1);
        while(tempBuffer.hasRemaining()) {
            socketChannel.read(tempBuffer);
        }
        tempBuffer.flip();
        byte len = tempBuffer.get();
        if(len == 19) {
            ByteBuffer buffer = ByteBuffer.allocate(68);
            buffer.put(len);
            while (buffer.hasRemaining()) {
                int bytesRead = socketChannel.read(buffer);
                if (bytesRead == -1) {
                    throw new IOException();
                }
            }
            buffer.flip();
            if(Handshake.IsHandshakeMessage(buffer.array())) {
                return buffer;
            } else {
                int lenInt = buffer.getInt();
                ByteBuffer message = ByteBuffer.allocate(lenInt);
                byte[] fakeHandShakeRemaining = new byte[64];
                message.put(fakeHandShakeRemaining);
                while(message.hasRemaining()) {
                    int bytesRead = socketChannel.read(message);
                    if(bytesRead == -1) {
                        throw new IOException();
                    }
                }
                message.flip();
                return message;
            }
        }
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
        ByteBuffer message = ByteBuffer.allocate(length);
        while (message.hasRemaining()) {
            int bytesRead = socketChannel.read(message);
            if (bytesRead == -1) {
                throw new IOException();
            }
        }
        message.flip();
        return message;
    }

    private PeerInfo FindPeerById(byte[] peerId) {
        for(PeerInfo peer : peers) {
            if(Arrays.equals(peer.GetPeerId(), peerId)) {
                return peer;
            }
        }
        System.out.println("Peer has not found");
        return null;
    }
}
