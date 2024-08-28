package org.example;

import org.example.message.Bitfield;

import java.net.InetSocketAddress;
import java.util.LinkedList;

public class PeerInfo {
    private final String ip;
    private final int port;
    private Peer.Status status = Peer.Status.NotConnected;
    private Bitfield bitfield;
    private LinkedList<Integer> receivedPieces;
    private byte[] peerId;

    public PeerInfo(String ip, int port) {
        receivedPieces = new LinkedList<>();
        this.ip = ip;
        this.port = port;
    }

    public void SetPeerId(byte[] peerId) {
        this.peerId = peerId;
    }
    public byte[] GetPeerId() {
        return peerId;
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
    public void AddNewReceivedPieceIndex(int index) {
        receivedPieces.add(index);
    }
    public boolean WereAnyPiecesReceived() {
        return !receivedPieces.isEmpty();
    }
    public int GetNewReceivedPieceIndex() {
        int index = receivedPieces.getFirst();
        receivedPieces.removeFirst();
        return index;

    }
}
