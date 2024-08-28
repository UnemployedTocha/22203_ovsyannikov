package org.example.message;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class PieceManager {
    private final String fileName;
    private Logger logger;
    private final int pieceSize;
    private final int piecesNum;
    private final long fileSize;
    public PieceManager(String fileName, int pieceSize, int piecesNum, long fileSize) {
        logger = LogManager.getLogger(PieceManager.class);
        this.piecesNum = piecesNum;
        this.pieceSize = pieceSize;
        this.fileSize = fileSize;
        this.fileName = fileName;
        System.out.println(fileSize + " " + piecesNum + " " + pieceSize);
    }

    public byte[] GetFilePiece(int pieceNum) throws IOException {
        try(RandomAccessFile file = new RandomAccessFile(fileName, "rw")){
            if (pieceNum >= this.piecesNum) {
                throw new IOException("Incorrect piece number");
            }
            byte[] piece;
            long begin = (long) pieceNum * pieceSize;

            file.seek(begin);
            if (pieceNum == this.piecesNum - 1) {
                piece = new byte[(int) (fileSize - begin)];
                file.read(piece, 0, (int) (fileSize - begin));
            } else {
                piece = new byte[pieceSize];
                file.read(piece, 0, pieceSize);
            }
            return piece;
        }
    }

    public void SetFilePiece(int pieceNum, byte[] piece) throws IOException{
        try(RandomAccessFile file = new RandomAccessFile(fileName, "rw")) {
            if (piece.length > pieceSize) {
                throw new IOException("Incorrect piece length");
            } else if (pieceNum >= piecesNum) {
                throw new IOException("Incorrect piece number");
            }
            long begin = (long) pieceNum * pieceSize;
            file.seek(begin);
            file.write(piece, 0, piece.length);
        }
    }

    static public byte GetMessageId(MessageType messageType) throws IOException {
        return switch (messageType) {
            case Have -> 4;
            case Bitfield -> 5;
            case Request -> 6;
            case Piece -> 7;
            default -> throw new IOException("Unknown message type");
        };
    }

    static public MessageType GetMessageType(int messageType) throws IOException {
        return switch (messageType) {
            case 4 -> MessageType.Have;
            case 5 -> MessageType.Bitfield;
            case 6 -> MessageType.Request;
            case 7 -> MessageType.Piece;
            default -> throw new IOException("Unknown message id");
        };
    }

    static public byte[] CalcPieceHash(byte[] piece) {
        MessageDigest messageDigest = null;
        try {
            messageDigest = MessageDigest.getInstance("SHA-1");
            messageDigest.update(piece);
        } catch (NoSuchAlgorithmException ex) {
            System.out.println(ex.getMessage());
        }

        assert messageDigest != null;
        return messageDigest.digest();
    }
}
