package org.example.message;

import org.example.util.Parser;
import org.example.PieceManager;
import org.example.util.Hash;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.Arrays;
import java.util.BitSet;

public class Bitfield {
    private BitSet bitSet;
    private final int length;

    public void PrintBitfield() {
        for(int i = 0; i < length; ++i) {
            System.out.print(bitSet.get(i) + " ");
        }
        System.out.print('\n');
    }

    public Bitfield(Parser parser, PieceManager pieceManager) throws IOException {
        length = parser.GetPiecesNum();
        bitSet = new BitSet(length);
        for(int i = 0; i < length; ++i) {
            byte[] pieceHash = Hash.CalcPieceHash(pieceManager.GetFilePiece(i));
            if(Arrays.equals(pieceHash, parser.GetTorrentPieceHash(i))) {
                bitSet.set(i);
            }
        }

    }

    public byte[] GetBitfieldMessage() {
        ByteBuffer buffer = ByteBuffer.allocate(4 + 1 + ((length + 7) / 8));
        buffer.putInt(1 + ((length + 7) / 8));
        try {
            buffer.put(MessageClassifier.GetMessageId(MessageType.Bitfield));
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
        buffer.put(bitSet.toByteArray());
        return buffer.array();
    }

    public int GetFirstRequestablePieceIndex(BitSet anotherBitSet) {
        for(int i = 0; i < length; ++i) {
            if(!bitSet.get(i) && anotherBitSet.get(i)) {
                return i;
            }
        }
        return -1;
    }
    public int GetNextRequestablePieceIndex(BitSet anotherBitSet, int index) {
        for(int i = index + 1; i < length; ++i) {
            if(!bitSet.get(i) && anotherBitSet.get(i)) {
                return i;
            }
        }
        return -1;
    }
    public int GetNumberOfPieces() {
        int sum = 0;
        for(int i = 0; i < length; ++i) {
            sum += (bitSet.get(i)) ? 1 : 0;
        }
        return sum;
    }
    public void Set(int index) {
        bitSet.set(index);
    }
    public void Nullify(int index) {
        bitSet.set(index);
    }
    public boolean PieceExists(int index) {
        return bitSet.get(index);
    }

}
