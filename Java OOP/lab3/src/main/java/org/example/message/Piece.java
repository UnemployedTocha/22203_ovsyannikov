package org.example.message;

import java.io.IOException;
import java.nio.ByteBuffer;

public class Piece {
    public static ByteBuffer Get(byte[] piece, int index, int begin) throws IOException {
        ByteBuffer pieceMessage = ByteBuffer.allocate(4 + 1 + 4 + 4 + piece.length);
        pieceMessage.putInt(1 + 4 + 4 + piece.length);
        pieceMessage.put(MessageClassifier.GetMessageId(MessageType.Piece));
        pieceMessage.putInt(index);
        pieceMessage.putInt(begin);
        pieceMessage.put(piece);
        pieceMessage.flip();
        return pieceMessage;
    }
}

