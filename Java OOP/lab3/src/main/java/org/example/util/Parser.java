package org.example.util;

import com.dampcake.bencode.Bencode;
import com.dampcake.bencode.BencodeInputStream;
import com.dampcake.bencode.Type;

import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteBuffer;
import java.util.Map;


public class Parser {
    private Map<String, Object> decodedInfo;
    private int pieceSize;
    private byte[] pieces;
    private long length;
    public Parser(String fileName) {
        InputStream in = Parser.class.getClassLoader().getResourceAsStream(fileName);
        BencodeInputStream bencodeIn = new BencodeInputStream(in);
// Wrong: 0F393F0904523F2D5B3F793F743F3F3F3F3F193F3F3F3F3F3F253F3F3F4A6F3D3B7B313F5A3F30473F463F285C3F314E3F4B133D153F3F3F773F183F3C3F4C5D293F3F003F3F403F3F1F4D743F057F1A3F783F560874633F3F3F4F3F3F170106493F013F39403F3F3E3F543F751F3F555E67543F3F3F453F3F1B123F3F3F3F053F063F3F3F405539383F2A4D3F0C3F2D017A3F3F7D3F3D733F3F123F3F3F3D3F5D1B3F2B3FF0021E3952003F06
// Right: 0F398E090452932D5BF4798E74C0C7F6AFB819B4AEFF85F28FFB2597A5C44A6F3D3B7B31CF5A9F3047E446D9285CD2314EED4B133D15F6E6D4778F18DC3CA04C5D29C8E900C3EC4092841F4D74D6057F1ADCBD78905608746396C9B0DB4F86E2170106499501E33940BFB03EB25495751F81555E6754F09CF3CA9945CED81B1286949C8B05A406D4F7C340553938CD2A4DBB0CE72D017AF6BA7DB33D73C2EE12CDDAA3833D9E5D1BE42B92C3B0021E395200E506
// ??   : 0F398E090452932D5BF4798E74C0C7F6AFB819B4AEFF85F28FFB2597A5C44A6F3D3B7B31CF5A9F3047E446D9285CD2314EED4B133D15F6E6D4778F18DC3CA04C5D29C8E900C3EC4092841F4D74D6057F1ADCBD78905608746396C9B0DB4F86E2170106499501E33940BFB03EB25495751F81555E6754F09CF3CA9945CED81B1286949C8B05A406D4F7C340553938CD2A4DBB0CE72D017AF6BA7DB33D73C2EE12CDDAA3833D9E5D1BE42B92C3B0021E395200E506
        Bencode bencode = new Bencode(true);
        try {
            Map<String, Object> map = bencode.decode(bencodeIn.readAllBytes(), Type.DICTIONARY);
            decodedInfo = (Map<String, Object>)map.get("info");

            pieces = ((ByteBuffer)decodedInfo.get("pieces")).array();
            length = ((long)decodedInfo.get("length"));
            long temp = ((long)decodedInfo.get("piece length"));
            pieceSize = (int)temp;
        } catch (IOException ex) {
            System.out.println(ex.getMessage());
        }
    }

    public byte[] GetInfoHash() {
        Bencode bencode = new Bencode();
        byte[] info = bencode.encode(decodedInfo);
        return Hash.CalcPieceHash(info);
    }
    public int GetPiecesNum() {
        return pieces.length / 20;
    }
    public int GetPieceSize() {
        return pieceSize;
    }
    public byte[] GetTorrentPieceHash(int pieceNum) {
        byte[] hash = new byte[20];
        System.arraycopy(pieces, pieceNum * 20, hash, 0, 20);
        return hash;
    }
    public long GetLength() {
        return length;
    }

}
