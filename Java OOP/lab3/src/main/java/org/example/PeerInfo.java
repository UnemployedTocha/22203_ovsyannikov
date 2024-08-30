package org.example;

import org.example.message.Bitfield;
import org.example.util.PeerId;

import java.net.InetSocketAddress;
import java.util.LinkedList;

public class PeerInfo {
    private final String ip;
    private final int port;
    private Peer.Status status = Peer.Status.NotConnected;
    private Bitfield bitfield;
    private byte[] peerId;
    private final LinkedList<Integer> receivedPieces;

    public PeerInfo(String ip, int port) {
        this.ip = ip;
        this.port = port;
        peerId = PeerId.Calc(port);
        receivedPieces = new LinkedList<>();
    }

    public void AddReceivedPieceIndex(int index) {
        receivedPieces.add(index);
    }
    public boolean WereAnyPiecesReceived() {
        return !receivedPieces.isEmpty();
    }
    public int GetReceivedPieceIndex() {
        return receivedPieces.removeFirst();
    }
    public void ClearReceivedPiecesIndexes() {
       receivedPieces.clear();
    }
    public void SetBitfield(Bitfield bitfield) {
        this.bitfield = bitfield;
    }
    public Bitfield GetBitfield() {
        return bitfield;
    }
    public InetSocketAddress GetInetSocketAddress() {
        return new InetSocketAddress(ip, port);
    }
    public Peer.Status GetStatus() {
        return status;
    }
    public void SetStatus(Peer.Status status) {
        this.status = status;
    }
    public int GetPort() {
        return port;
    }
    public byte[] GetPeerId() {
        return peerId;
    }
}
