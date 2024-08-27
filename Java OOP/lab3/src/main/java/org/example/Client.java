package org.example;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.example.message.Bitfield;
import org.example.message.Handshake;
import org.example.message.MessageType;
import org.example.message.PieceManager;

import java.io.File;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.SocketChannel;
import java.util.*;

public class Client implements Runnable{
    final private int PIECE_SIZE;
    private Logger logger;
    private Selector selector;
    private Parser parser;
    private PieceManager pieceManager;
    private final int port;
    private List<PeerInfo> peers;
    Bitfield bitfield;

    public Client(String ip, int port, List<PeerInfo> servers, Bitfield bitfield, Parser parser, PieceManager pieceManager, String fileName) {
        logger = LogManager.getLogger(Client.class);
        this.port = port;
        this.peers = servers;
        this.bitfield = bitfield;
        this.parser = parser;
        this.pieceManager = pieceManager;
        this.PIECE_SIZE = parser.GetPieceSize();

    }
    private void RegisterConnections(Selector selector, List<PeerInfo> peers) throws IOException {
        for(PeerInfo peer : peers) {
            if(peer.GetStatus() != Peer.Status.NotConnected) {
                continue;
            }
            SocketChannel channel = SocketChannel.open();
            channel.configureBlocking(false);
            channel.connect(peer.GetInetSocketAddress());
            channel.register(selector, SelectionKey.OP_CONNECT, peer);
        }
    }

    @Override
    public void run() {
        try {
            selector = Selector.open();
            logger.info("Running client at port: " + port);
            while(true) {
                RegisterConnections(selector, peers);
                selector.select();
                Set<SelectionKey> keys = selector.selectedKeys();
                Iterator<SelectionKey> it = keys.iterator();
                while(it.hasNext()) {
                    SelectionKey key = it.next();
                    it.remove();

                    if(key.isValid() && key.isConnectable() && ((PeerInfo)key.attachment()).GetStatus() == Peer.Status.NotConnected)  {
                        HandleConnection(key);
                    }
                    if(key.isValid() && key.isWritable()) {
                        HandleWrite(key);
                    }
                    if(key.isValid() && key.isReadable()) {
                        HandleRead(key);
                    }

                }
            }

        } catch (IOException ex) {
            logger.info("Client stopped");
            System.out.println(ex.getMessage());
        }
    }

    private void HandleConnection(SelectionKey key) throws IOException {
        try {
            ((SocketChannel)key.channel()).finishConnect();
        } catch (IOException ex) {
            ((PeerInfo)key.attachment()).SetStatus(Peer.Status.NotConnected);
            key.channel().close();
            key.cancel();
            return;
        }

        key.interestOps(SelectionKey.OP_WRITE);
        ((PeerInfo)key.attachment()).SetStatus(Peer.Status.Connected);
        logger.info("Server {} connected!", ((PeerInfo) key.attachment()).GetInetSocketAddress());

    }

    private void HandleWrite(SelectionKey key) throws IOException {
        try {
            switch (((PeerInfo) key.attachment()).GetStatus()) {
                case Peer.Status.Connected -> SendHandshake(key);
                case Peer.Status.SendBitfield -> SendBitfield(key);
                case Peer.Status.SendRequest -> SendRequest(key);
                case Peer.Status.SentRequest -> SendHave(key);
            }
        } catch (IOException ex) {
            key.cancel();
            key.channel().close();
            ((PeerInfo)key.attachment()).SetStatus(Peer.Status.NotConnected);
        }
    }

    private void HandleRead(SelectionKey key) throws IOException {
        try {
            switch (((PeerInfo) key.attachment()).GetStatus()) {
                case Peer.Status.SentHandshake -> ReceiveHandshake(key);
                case Peer.Status.SentBitfield -> ReceiveBitfield(key);
                case Peer.Status.SentRequest -> ReceivePiece(key);
            }
        } catch (IOException ex) {
            key.cancel();
            key.channel().close();
            ((PeerInfo)key.attachment()).SetStatus(Peer.Status.NotConnected);
        }
    }


    private void SendHandshake(SelectionKey key) throws IOException{
        byte[] message = (new Handshake(parser.GetInfoHash())).GetHandshakeMessage();
        SocketChannel socketChannel = (SocketChannel) key.channel();

        ByteBuffer buffer = ByteBuffer.wrap(message);
        while(buffer.hasRemaining()) {
            socketChannel.write(buffer);
        }

        key.interestOps(SelectionKey.OP_READ);
        ((PeerInfo)key.attachment()).SetStatus(Peer.Status.SentHandshake);
        logger.info("Sent handshake to peer: {}", ((PeerInfo) key.attachment()).GetPort());
    }

    private void SendBitfield(SelectionKey key) throws IOException {
        SocketChannel socketChannel = (SocketChannel) key.channel();
        byte[] message = bitfield.GetBitfieldMessage();

        ByteBuffer buffer = ByteBuffer.wrap(message);
        while (buffer.hasRemaining()) {
            socketChannel.write(buffer);
        }
//        System.out.print("Bitfield client sent: ");
//        bitfield.PrintBitfield();

        key.interestOps(SelectionKey.OP_READ);
        ((PeerInfo)key.attachment()).SetStatus(Peer.Status.SentBitfield);
        logger.info("Sent bitfield to peer: {}", ((PeerInfo) key.attachment()).GetPort());
    }

    private void SendRequest(SelectionKey key) throws IOException{
        SocketChannel socketChannel = (SocketChannel) key.channel();
        int index = bitfield.GetFirstRequestablePieceIndex(((PeerInfo)key.attachment()).GetBitSet());
        if(index != -1) {
            byte messageId = PieceManager.GetMessageId(MessageType.Request);
            int begin = 0;
            ByteBuffer buffer = ByteBuffer.allocate(4 + 1 + 4 + 4 + 4);
            buffer.putInt(13);
            buffer.put(messageId);
            buffer.putInt(index);
            buffer.putInt(begin);
            buffer.putInt(PIECE_SIZE);
            buffer.flip();

            while(buffer.hasRemaining()) {
                socketChannel.write(buffer);
            }

            key.interestOps(SelectionKey.OP_READ);
            ((PeerInfo)key.attachment()).SetStatus(Peer.Status.SentRequest);
            logger.info("Sent request: {} to peer: {}", index, ((PeerInfo) key.attachment()).GetPort());
        }
    }

    private void SendHave(SelectionKey key) {
        SocketChannel socketChannel = (SocketChannel) key.channel();
    }

    private void ReceiveHandshake(SelectionKey key) throws IOException {
        SocketChannel socketChannel = (SocketChannel)key.channel();
        ByteBuffer buffer = ByteBuffer.allocate(68);

        int bytesRead;
        while(buffer.hasRemaining()) {
            bytesRead = socketChannel.read(buffer);
            if(bytesRead == -1) {
                throw new IOException();
            }
        }

        if(Handshake.IsHandshakeMessage(buffer.array())) {
            // Добавить проверку инфохэша??
            ((PeerInfo)key.attachment()).SetStatus(Peer.Status.SendBitfield);
            key.interestOps(SelectionKey.OP_WRITE);
            logger.info("Received handshake from peer: {}", ((PeerInfo) key.attachment()).GetPort());
        } else {
            logger.info("Incorrect answer from server (handshake message)");
        }
    }

    private void ReceiveBitfield(SelectionKey key) throws IOException {
        SocketChannel socketChannel = (SocketChannel) key.channel();
        ByteBuffer buffer = ByteBuffer.allocate(4);

        while (buffer.hasRemaining()) {
            int bytesRead = socketChannel.read(buffer);
            if(bytesRead == -1) {
                throw new IOException();
            }
        }
        buffer.flip();
        int messageLength = buffer.getInt();

        buffer = ByteBuffer.allocate(messageLength);
        while (buffer.hasRemaining()) {
            int bytesRead = socketChannel.read(buffer);
            if(bytesRead == -1) {
                throw new IOException("Socket channel closed");
            }
        }
        buffer.flip();
        if (buffer.get() == PieceManager.GetMessageId(MessageType.Bitfield)) {
            BitSet peerBitSet = new BitSet(parser.GetPiecesNum());

            byte[] bitsetBytes = new byte[messageLength - 1];
            buffer.get(bitsetBytes, 0, messageLength - 1);
            for(int i = 0; i < parser.GetPiecesNum(); ++i) {
                if(((bitsetBytes[i / 8] & (1 << (i % 8)))) != 0) {
                    peerBitSet.set(i);
                }
            }

            ((PeerInfo)key.attachment()).SetBitset(peerBitSet);
            ((PeerInfo)key.attachment()).SetStatus(Peer.Status.SendRequest);
            key.interestOps(SelectionKey.OP_WRITE);
            logger.info("Received bitfield from peer: {}", ((PeerInfo) key.attachment()).GetPort());
            return;
        }
        throw new IOException("Unknown message type");
    }

    private void ReceivePiece(SelectionKey key) throws IOException{
        SocketChannel socketChannel = (SocketChannel) key.channel();
        ByteBuffer buffer = ByteBuffer.allocate(4);

        while (buffer.hasRemaining()) {
            int bytesRead = socketChannel.read(buffer);
            if(bytesRead == -1) {
                throw new IOException();
            }
        }

        buffer.flip();
        int messageLen = buffer.getInt();
        buffer = ByteBuffer.allocate(messageLen);
        while (buffer.hasRemaining()) {
            int bytesRead = socketChannel.read(buffer);
            if(bytesRead == -1) {
                throw new IOException("Socket channel closed");
            }
        }
        buffer.flip();

        if(buffer.get() == PieceManager.GetMessageId(MessageType.Piece)) {
            int pieceIndex = buffer.getInt();
            int begin = buffer.getInt();
            byte[] piece = new byte[messageLen - 9];
            buffer.get(piece, 0, messageLen - 9);
            if(Arrays.equals(PieceManager.CalcPieceHash(piece), parser.GetTorrentPieceHash(pieceIndex))) {
                pieceManager.SetFilePiece(pieceIndex, piece);
                bitfield.Set(pieceIndex);
            } else {
                key.interestOps(SelectionKey.OP_WRITE);
                ((PeerInfo)key.attachment()).SetStatus(Peer.Status.SendRequest);
                logger.info("INCORRECT PIECE, PIECE LEN = {}, PIECE INDEX = {}, OFFSET = {}", messageLen - 9, pieceIndex, begin);
                return;
                //throw new IOException("Incorrect received piece hash");
            }

            key.interestOps(SelectionKey.OP_WRITE);
            ((PeerInfo)key.attachment()).SetStatus(Peer.Status.SendRequest);
            logger.info("Received piece: {}from peer: {}", pieceIndex, ((PeerInfo) key.attachment()).GetPort());
        }
    }

}
