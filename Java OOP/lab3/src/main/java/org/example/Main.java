package org.example;

import org.example.util.PeerId;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Random;

public class Main {
    public static void main(String[] args) {
        List<PeerInfo> peers = new ArrayList<>();
        for(int i = 0; i < 5; ++i) {
            peers.add(new PeerInfo("127.0.0.1", 8000 + i));
        }

//        GenerateFile();
        Peer peer = new Peer(8000, peers, "VeryBigTestFile");
        peer.Start();

    }

    public static void GenerateFile() {
        String fileName = "VeryBigTestFile.txt";
        long fileSize = 4 * 1024L * 1024 * 1024;
        long size = 0;
        Random random = new Random();
        try(BufferedWriter writer = new BufferedWriter(new FileWriter(fileName))) {
            while (size < fileSize) {
                writer.write('A' + random.nextInt(26));
                size += 1;
            }
            System.out.println("Файл успешно создан: " + fileName);
        } catch(IOException e) {
            System.out.println("Ошибка записи в файл: " + e.getMessage());
        }
    }


}