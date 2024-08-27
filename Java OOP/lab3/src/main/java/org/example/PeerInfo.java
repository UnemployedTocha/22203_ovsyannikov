package org.example;

import org.example.message.Bitfield;

import java.net.InetSocketAddress;
import java.util.BitSet;

public class PeerInfo {
    private final String ip;
    private final int port;
    private Peer.Status status = Peer.Status.NotConnected;
    private BitSet bitset;

    public PeerInfo(String ip, int port) {
        this.ip = ip;
        this.port = port;
    }

    public void SetBitset(BitSet bitset) {
        this.bitset = bitset;
    }
    public BitSet GetBitSet() {
        return bitset;
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
}
