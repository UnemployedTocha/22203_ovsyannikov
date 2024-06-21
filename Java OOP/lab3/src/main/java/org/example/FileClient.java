package org.example;

import java.io.*;
import java.net.*;
import java.util.List;
import java.util.Scanner;


public class FileClient {
    private final int BUFFER_SIZE = 4096;
    private Socket clientSocket;
    private PrintWriter writer;
    private BufferedReader reader;

    public FileClient(String serverAddress , int port) throws IOException{
        clientSocket = new Socket(serverAddress, port);
        writer = new PrintWriter(clientSocket.getOutputStream(), true);
        reader = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        System.out.println("Connected to the server at " + serverAddress + ":" + port);
    }

    public void RequestFileList() throws IOException{
        writer.println("LIST");
        System.out.println("Files on server: ");
        String line;
        while(!(line = reader.readLine()).equals("END")) {
            System.out.println(line);
        }
    }
    public void UploadFile(String filePath) throws IOException{
        File file = new File(filePath);
        if(file.exists()) {
            writer.println("UPLOAD");
            writer.println(file.getName());
            try(FileInputStream fileIn = new FileInputStream(file);
                BufferedInputStream fileStream = new BufferedInputStream(fileIn);
                OutputStream out = clientSocket.getOutputStream()) {
                    byte[] buffer = new byte[BUFFER_SIZE];
                    int bytesRead;
                    while((bytesRead = fileStream.read(buffer)) != -1) {
                        out.write(buffer, 0, bytesRead);
                    }
                    out.flush();
                System.out.println("File upload was successful");
            }
        } else {
            System.out.println("File doesn`t exist");
        }
    }

    public void DownloadFile(String fileName) throws IOException {
        writer.println("DOWNLOAD");
        writer.println(fileName);
        try (FileOutputStream fileOut = new FileOutputStream("download_" + fileName);
             BufferedOutputStream fileStream = new BufferedOutputStream(fileOut);
             InputStream in = clientSocket.getInputStream()){

            byte[] buffer = new byte[BUFFER_SIZE];
            int bytesRead;
            while((bytesRead = in.read(buffer)) != -1) {
                if (bytesRead == 0) break;
                fileStream.write(buffer, 0, bytesRead);
            }
            System.out.println("DA BLYAT");
            fileStream.flush();
            System.out.println("File downloaded successfully");

        }
    }

    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) {
            System.out.print("Enter server address: ");
            String serverAddress = scanner.nextLine();
            System.out.print("Enter server port: ");
            int port = scanner.nextInt();
            scanner.nextLine();

            FileClient client = new FileClient(serverAddress, port);
            client.RequestFileList();

            System.out.println("Choose an option:\n1. Upload a file\n2. Download a file");
            int choice = scanner.nextInt();
            scanner.nextLine();

            switch (choice) {
                case 1:
                    System.out.print("Enter file path to upload: ");
                    String filePathToUpload = scanner.nextLine();
                    client.UploadFile(filePathToUpload);
                    break;
                case 2:
                    System.out.print("Enter file name to download: ");
                    String fileNameToDownload = scanner.nextLine();
                    client.DownloadFile(fileNameToDownload);
                    break;
                default:
                    System.out.println("Invalid option selected.");
                    break;
            }
        } catch (IOException e) {
            System.out.println("Error: " + e.getMessage());
            e.printStackTrace();
        }
    }
}

