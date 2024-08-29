package org.example;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.example.message.Bitfield;
import org.example.util.Hash;
import org.example.util.Parser;

import java.io.File;
import java.io.IOException;
import java.util.Arrays;
import java.util.Iterator;
import java.util.List;

public class Peer {
    public enum Status {
        NotConnected,
        Connected,
        SentHandshake,
        SendBitfield,
        SentBitfield,
        SendRequest,
        SentRequest,
    }
    private final Logger logger = LogManager.getLogger(Client.class);
    private final int port;
    private List<PeerInfo> peers;
    private final String filePath;


    public Peer(int port, List<PeerInfo> peers, String fileName) {
        this.port = port;
        this.peers = peers;
        this.filePath = fileName;

        Iterator<PeerInfo> it = this.peers.iterator();
        while(it.hasNext()) {
            if(it.next().GetPort() == this.port) {
                it.remove();
            }
        }
    }

    public void Start() {
        File file = new File(filePath + ".txt");
        Parser parser = new Parser(filePath + ".torrent");
        PieceManager pieceManager = new PieceManager(file.getName(), parser.GetPieceSize(), parser.GetPiecesNum(), parser.GetLength());
        Bitfield bitfield = GetBitField(parser, pieceManager);

        logger.info("Number of pieces: {}/{}", bitfield.GetNumberOfPieces(), parser.GetPiecesNum());

        Thread serverThread = new Thread(new Server("127.0.0.1", port, bitfield, parser, pieceManager, peers));
        serverThread.start();
        Client client = new Client(port, peers, bitfield, parser, pieceManager);
        client.run();
    }

    private Bitfield GetBitField(Parser parser, PieceManager pieceManager) {
        Bitfield bitfield = null;
        try {
            bitfield = new Bitfield(parser, pieceManager);
        } catch(IOException ex) {
            System.out.println(ex.getMessage());
        }
        return bitfield;
    }



    public void GenerateHalfOfFile(PieceManager pieceManager, Parser parser, boolean part, String fileName) {
        try {
            File file = new File(fileName + ".txt");
            PieceManager pieceManager2 = new PieceManager(file.getName(), parser.GetPieceSize(), parser.GetPiecesNum(), parser.GetLength());
            if (!part) {
                System.out.println("End: " + ((parser.GetPiecesNum() / 2) + 1));
                for (int i = 0; i < (parser.GetPiecesNum() / 2) + 1; ++i) {
                    byte[] piece = pieceManager.GetFilePiece(i);
                    if(!Arrays.equals(Hash.CalcPieceHash(piece), parser.GetTorrentPieceHash(i))) {
                        logger.info("FILE WITH ERROR");
                    }
                    pieceManager2.SetFilePiece(i, piece);
                    if(!Arrays.equals(Hash.CalcPieceHash(pieceManager2.GetFilePiece(i)), parser.GetTorrentPieceHash(i))) {
                        logger.info("FILE WITH ERROR");
                    }
                }
            } else {
                System.out.println("Start: " + (parser.GetPiecesNum() / 2));
                for (int i = (parser.GetPiecesNum() / 2); i < parser.GetPiecesNum(); ++i) {
                    byte[] piece = pieceManager.GetFilePiece(i);
                    if(!Arrays.equals(Hash.CalcPieceHash(piece), parser.GetTorrentPieceHash(i))) {
                        logger.info("GENERATED FILE WITH ERROR");
                    }
                    pieceManager2.SetFilePiece(i, piece);
                    if(!Arrays.equals(Hash.CalcPieceHash(pieceManager2.GetFilePiece(i)), parser.GetTorrentPieceHash(i))) {
                        logger.info("GENERATED FILE WITH ERROR");
                    }
                }
            }
        } catch (IOException ex) {
            System.out.println(ex.getMessage());
        }
    }
}
