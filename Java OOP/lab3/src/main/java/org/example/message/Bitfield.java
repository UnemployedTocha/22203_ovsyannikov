package org.example.message;

import org.example.util.Parser;
import org.example.PieceManager;
import org.example.util.Hash;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.Arrays;
import java.util.BitSet;
import java.util.concurrent.ConcurrentHashMap;

public class Bitfield {
//    private BitSet bitSet;
    ConcurrentHashMap<Integer, Boolean> bitset;

    private final int length;

    public void PrintBitfield() {
        for(int i = 0; i < length; ++i) {
            System.out.print(bitset.get(i) + " ");
        }
        System.out.print('\n');
    }
    public Bitfield(BitSet bitSet, int length) {
        this.length = length;

        bitset = new ConcurrentHashMap<>();
        for(int i = 0; i < length; ++i) {
            if(bitSet.get(i)) {
                bitset.put(i, true);
            } else {
                bitset.put(i, false);
            }
        }
    }
    public boolean IsDownloadFinished() {
        for(int i = 0; i < length; ++i) {
            if(!bitset.get(i)) {
                return false;
            }
        }
        return true;
    }

    public Bitfield(Parser parser, PieceManager pieceManager) throws IOException {
        length = parser.GetPiecesNum();

        bitset = new ConcurrentHashMap<>();
        for(int i = 0; i < length; ++i) {
            byte[] pieceHash = pieceHash = Hash.CalcPieceHash(pieceManager.GetFilePiece(i));
            if(Arrays.equals(pieceHash, parser.GetTorrentPieceHash(i))) {
                bitset.put(i, true);
            } else {
                bitset.put(i, false);
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
        buffer.put(this.ToByteArray());
        return buffer.array();
    }

    private byte[] ToByteArray() {
        byte[] arr = new byte[(length + 7) / 8];
        for(int i = 0; i < length; ++i) {
            int value = bitset.get(i) ? 1 : 0;
            arr[i / 8] += (byte)((value << (i % 8)));
        }
        return arr;
    }

    public int GetFirstRequestablePieceIndex(Bitfield anotherBitfield) {
        for(int i = 0; i < length; ++i) {
            if(!bitset.get(i) && anotherBitfield.bitset.get(i)) {
                return i;
            }
        }
        return -1;
    }
    public int GetNextRequestablePieceIndex(Bitfield anotherBitfield, int index) {
        for(int i = index + 1; i < length; ++i) {
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
    public void Nullify(int index) {
        bitset.put(index, false);
    }
    public boolean PieceExists(int index) {
        return bitset.get(index);
    }

}
