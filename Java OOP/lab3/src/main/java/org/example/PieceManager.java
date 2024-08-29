package org.example;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.io.IOException;
import java.io.RandomAccessFile;

public class PieceManager {
    Logger logger;
    private final String fileName;
    private final int pieceSize;
    private final int piecesNum;
    private final long fileSize;

    public PieceManager(String fileName, int pieceSize, int piecesNum, long fileSize) {
        logger = LogManager.getLogger(Client.class);
        this.piecesNum = piecesNum;
        this.pieceSize = pieceSize;
        this.fileSize = fileSize;
        this.fileName = fileName;
        System.out.println(fileSize + " " + piecesNum + " " + pieceSize);
    }

    public byte[] GetFilePiece(int pieceNum) throws IOException {
        try (RandomAccessFile file = new RandomAccessFile(fileName, "rw")) {
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

    public void SetFilePiece(int pieceNum, byte[] piece) throws IOException {
        try (RandomAccessFile file = new RandomAccessFile(fileName, "rw")) {
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
}

