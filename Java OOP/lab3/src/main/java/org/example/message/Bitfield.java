package org.example.message;

import org.example.Parser;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.Arrays;
import java.util.BitSet;
import java.util.concurrent.ConcurrentHashMap;

public class Bitfield {
    private final int length;
    private final ConcurrentHashMap<Integer, Boolean> bitset;

    public void PrintBitfield() {
        for(int i = 0; i < length; ++i) {
            System.out.print(bitset.get(i) + " ");
        }
        System.out.print('\n');
    }

    public Bitfield(Parser parser, PieceManager pieceManager) throws IOException {
        length = parser.GetPiecesNum();
        bitset = new ConcurrentHashMap<>();
        for(int i = 0; i < length; ++i) {
            byte[] pieceHash = PieceManager.CalcPieceHash(pieceManager.GetFilePiece(i));
            if(Arrays.equals(pieceHash, parser.GetTorrentPieceHash(i))) {
                bitset.put(i, true);
            } else {
                bitset.put(i, false);
            }
        }
    }

    public Bitfield(byte[] bytes, int length) {
        this.length = length;
        bitset = new ConcurrentHashMap<>();
        for(int i = 0; i < length; ++i) {
            boolean value = (bytes[i / 8] & (1 << i % 8)) != 1;
            bitset.put(i, value);
        }
    }

    public byte[] GetBitfieldMessage() {
        ByteBuffer buffer = ByteBuffer.allocate(4 + 1 + ((length + 7) / 8));
        buffer.putInt(1 + ((length + 7) / 8));
        try {
            buffer.put(PieceManager.GetMessageId(MessageType.Bitfield));
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        buffer.put(this.ToByteArray());
        return buffer.array();
    }

    private byte[] ToByteArray() {
        byte[] bytes = new byte[(length + 7) / 8];
        for(int i = 0; i < length; ++i) {
            int value = bitset.get(i) ? 1 : 0;
            bytes[i / 8] += (byte)(value << (i % 8));
        }
        return bytes;
    }
    public int GetFirstRequestablePieceIndex(Bitfield anotherBitfield) {
        for(int i = 0; i < length; ++i) {
            if(!bitset.get(i) && anotherBitfield.bitset.get(i)) {
                return i;
            }
        }
        return -1;
    }
    public int GetNumberOfPieces() {
        int sum = 0;
        for(int i = 0; i < length; ++i) {
            sum += (bitset.get(i)) ? 1 : 0;
        }
        return sum;
    }
    public void Set(int index) {
        bitset.put(index, true);
    }

    public boolean PieceExists(int index) {
        return bitset.get(index);
    }

}
