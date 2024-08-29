package org.example.message;

import java.io.IOException;

public class MessageClassifier {
    public static byte GetMessageId(MessageType messageType) throws IOException{
        return switch (messageType) {
            case Have -> 4;
            case Bitfield -> 5;
            case Request -> 6;
            case Piece -> 7;
            default -> throw new IOException("Unknown message type");
        };
    }

    public static MessageType GetMessageType(byte messageId) throws IOException{
        return switch (messageId) {
            case 4 -> MessageType.Have;
            case 5 -> MessageType.Bitfield;
            case 6 -> MessageType.Request;
            case 7 -> MessageType.Piece;
            default -> throw new IOException("Unknown message id");
        };
    }
}
