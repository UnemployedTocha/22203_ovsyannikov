package org.example.gameField;

import org.example.entities.*;

import java.io.InputStream;
import java.util.*;

public class GameField {
    public enum FieldType {
        EMPTY(0),
        WALL(1),
        PORTAL(2),
        BLOCK_WITH_COINS(3),
        POWER_PELLET(4),
        FRUIT(5),
        PLAYER(6),
        BLINKY(7),
        PINKY(8),
        INKY(9),
        CLYDE(10);
        private int code;
        private HashMap<Integer, FieldType> map = new HashMap<>();

        FieldType(int i) {
            code = i;
        }

        public int GetCode() {
            return code;
        }
        static public FieldType ValueOf(int code){
            return switch (code) {
                case 0 -> EMPTY;
                case 1 -> WALL;
                case 2 -> PORTAL;
                case 3 -> BLOCK_WITH_COINS;
                case 4 -> POWER_PELLET;
                case 5 -> FRUIT;
                case 6 -> PLAYER;
                case 7 -> BLINKY;
                case 8 -> PINKY;
                case 9 -> INKY;
                case 10 -> CLYDE;
                default -> throw new RuntimeException("Unexpected fieldType: " + code);
            };

        }
    };
    private final int tileSize;
    private final int rowsNum = 31;
    private final int colsNum = 28;
    int totalCoins = 0;
    int collectedCoins = 0;

    int[] playerResCords;
    int[] blinkyResCords;
    int[] pinkyResCords;
    int[] inkyResCords;
    int[] clydeResCords;
    List<int[][]> linkedPortalsCords;

    private FieldType[][] gameField = new FieldType[rowsNum][colsNum];
    public void CollectCoin(int i, int j) {
        collectedCoins++;
        gameField[i][j] = FieldType.EMPTY;
    }
    public void CollectPowerPellet(int i, int j) {
        gameField[i][j] = FieldType.EMPTY;
    }

    public FieldType[][] GetGameField() {
        return gameField;
    }

    public GameField(Player player, List<Ghost> ghosts, int tileSize) {
        playerResCords = new int[2];
        blinkyResCords = new int[2];
        inkyResCords = new int[2];
        clydeResCords = new int[2];
        pinkyResCords = new int[2];
        linkedPortalsCords = new ArrayList<>();
        this.tileSize = tileSize;
        LoadGame(player, ghosts);
    }
    public void LoadGame(Player player, List<Ghost> ghosts) {
        InputStream in = GameField.class.getClassLoader().getResourceAsStream("GameField.txt");
        assert in != null;
        Scanner scanner = new Scanner(in);
        ScanGameField(scanner, player, ghosts);
    }

    public void LocalRestart(Player player, List<Ghost> ghosts) {
    player.SetLifesNum(player.GetLifesNum() - 1);
        for(Ghost ghost : ghosts) {
            ghost.RespawnGhost();
            switch (ghost) {
                case Blinky blinky -> {
                    ghost.SetX(blinkyResCords[1] * tileSize);
                    ghost.SetY(blinkyResCords[0] * tileSize);
                }
                case Pinky pinky -> {
                    ghost.SetX(pinkyResCords[1] * tileSize);
                    ghost.SetY(pinkyResCords[0] * tileSize);
                }
                case Inky inky -> {
                    ghost.SetX(inkyResCords[1] * tileSize);
                    ghost.SetY(inkyResCords[0] * tileSize);
                }
                case Clyde clyde -> {
                    ghost.SetX(clydeResCords[1] * tileSize);
                    ghost.SetY(clydeResCords[0] * tileSize);
                }
                default -> {
                }
            }
        }
        player.SetX(playerResCords[1] * tileSize);
        player.SetY(playerResCords[0] * tileSize);
    }
    public void GlobalLevelRestart(Player player, List<Ghost> ghosts) {
        player.SetLifesNum(3);
        player.NullifyScores();
        collectedCoins = 0;
        player.SetX(playerResCords[1] * tileSize);
        player.SetY(playerResCords[0] * tileSize);
        int size = ghosts.size();
        for(int i = 0; i < size; ++i) {
            Ghost ghost = ghosts.getFirst();
            ghosts.removeFirst();
            switch (ghost) {
                case Blinky blinky -> {
                    ghosts.addLast(new Blinky(player, this, blinkyResCords[1] * tileSize, blinkyResCords[0] * tileSize, tileSize));
                }
                case Pinky pinky -> {
                    ghosts.addLast(new Pinky(player, this, pinkyResCords[1] * tileSize, pinkyResCords[0] * tileSize, tileSize));
                }
                case Inky inky -> {
                    ghosts.addLast(new Inky(player, this, inkyResCords[1] * tileSize, inkyResCords[0] * tileSize, tileSize));
                }
                case Clyde clyde -> {
                    ghosts.addLast(new Clyde(player, this, clydeResCords[1] * tileSize, clydeResCords[0] * tileSize, tileSize));
                }
                default -> {
                }
            }
        }


        InputStream in = GameField.class.getClassLoader().getResourceAsStream("GameField.txt");
        assert in != null;
        Scanner scanner = new Scanner(in);
        int i = 0;
        while(scanner.hasNextLine()) {
            String line = scanner.nextLine();
            StringTokenizer tokens = new StringTokenizer(line, " ");
            int j = 0;
            while(tokens.hasMoreTokens()){
                String s = tokens.nextToken();
                FieldType obj = FieldType.ValueOf(Integer.parseInt(s));
                switch (obj) {

                    case BLOCK_WITH_COINS:
                        gameField[i][j] = FieldType.BLOCK_WITH_COINS;

                        break;
                }
                gameField[i][j] = obj;
                ++j;
            }
            ++i;
        }
}

    private void ScanGameField(Scanner scanner, Player player, List<Ghost> ghosts) {
        int i = 0;
        while(scanner.hasNextLine()) {
            String line = scanner.nextLine();
            StringTokenizer tokens = new StringTokenizer(line, " ");
            int j = 0;
            while(tokens.hasMoreTokens()){
                String s = tokens.nextToken();
                FieldType obj = FieldType.ValueOf(Integer.parseInt(s));
                switch (obj) {
                    case PLAYER:
                        player.SetGameField(this);
                        playerResCords[0] = i;
                        playerResCords[1] = j;
                        player.SetX(j * tileSize);
                        player.SetY(i * tileSize);
                        break;
                    case BLINKY:
                        Blinky blinky = new Blinky(player, this, j * tileSize, i * tileSize, tileSize);
                        blinkyResCords[0] = i;
                        blinkyResCords[1] = j;
                        ghosts.add(blinky);
                        break;
                    case PINKY:
                        Pinky pinky = new Pinky(player, this, j * tileSize, i * tileSize, tileSize);
                        pinkyResCords[0] = i;
                        pinkyResCords[1] = j;
                        ghosts.add(pinky);
                        break;
                    case INKY:
                        Inky inky = new Inky(player, this, j * tileSize, i * tileSize, tileSize);
                        inkyResCords[0] = i;
                        inkyResCords[1] = j;
                        ghosts.add(inky);
                        break;
                    case CLYDE:
                        clydeResCords[0] = i;
                        clydeResCords[1] = j;
                        Clyde clyde = new Clyde(player, this, j * tileSize, i * tileSize, tileSize);
                        ghosts.add(clyde);
                        break;
                    case PORTAL:
                        int[][] cords = new int[2][2];
                        cords[0][0] = i;
                        cords[0][1] = j;
                        if (i == 0) {
                            cords[1][0] = rowsNum - 1;
                            cords[1][1] = j;
                        } else if (i == rowsNum) {
                            cords[1][0] = 0;
                            cords[1][1] = j;
                        } else if (j == 0) {
                            cords[1][0] = i;
                            cords[1][1] = colsNum - 1;
                        } else {
                            cords[1][0] = i;
                            cords[1][1] = 0;
                        }
                        linkedPortalsCords.add(cords);
                        break;
                    case BLOCK_WITH_COINS:
                        totalCoins++;
                        break;
                }
                gameField[i][j] = obj;
                ++j;
            }
            ++i;
        }
    }
    public boolean isLevelCompleted() {
        return collectedCoins == totalCoins;
    }
    public FieldType GetEntityCell(Entity entity) {
        return gameField[entity.GetY() / tileSize][entity.GetX() / tileSize];
    }
    public List<int[][]> GetPortalCords() {
        return linkedPortalsCords;
    }
    public int GetRowsNum() {
        return rowsNum;
    }
    public int GetColsNum() {
        return colsNum;
    }
    public void update(List<Ghost> ghosts) {
        for(Ghost g : ghosts) {
            g.UpdateSpeed(this);
            g.Update();
        }
    }
}
