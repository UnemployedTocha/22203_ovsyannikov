package org.example;

import java.util.BitSet;

public class LoadingManager {
    private BitSet bitset;
    private int length;
    public LoadingManager(int piecesNum) {
        length = piecesNum;
        bitset = new BitSet(piecesNum);
    }

    public void StartLoadingPiece(int index) {
        bitset.set(index);
    }

    public boolean IsPieceLoading(int index) {
        return bitset.get(index);
    }

    public void StopLoading(int index) {
        bitset.clear(index);
    }
}
