package org.example.utility;

import org.example.entities.Blinky;
import org.example.entities.Ghost;
import org.example.entities.Pinky;
import org.example.entities.Player;
import org.example.gameField.GameField;
import jdk.swing.interop.SwingInterOpUtils;

import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

public class Utility {
    private static final int[] ROW_OFFSETS = {-1, 0, 1, 0};
    private static final int[] COL_OFFSETS = {0, 1, 0, -1};

    private static final String[] DIRECTIONS = {"UP", "RIGHT", "DOWN", "LEFT"};
    public static int[] PathSpeed(GameField.FieldType[][] matrix, int startRow, int startCol, int endRow, int endCol, int dx, int dy) {
        int rows = matrix.length;
        int cols = matrix[0].length;
        int[][] distances = new int[rows][cols];
        int[][] prevDirection = new int[rows][cols];

        for(int[] row : distances) {
            Arrays.fill(row, Integer.MAX_VALUE);
        }
        for(int[] row : prevDirection) {
            Arrays.fill(row, -1);
        }
        distances[startRow][startCol] = 0;
        Queue<int[]> queue = new LinkedList<>();
        queue.add(new int[]{startRow, startCol, -1});

        while (!queue.isEmpty()) {
            int[] cell = queue.poll();
            int row = cell[0];
            int col = cell[1];
            int dir = cell[2];
            int currDistance = distances[row][col];

            for(int i = 0; i < 4; i++) {
                int newRow = row + ROW_OFFSETS[i];
                int newCol = col + COL_OFFSETS[i];
                if(newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
                    matrix[newRow][newCol] != GameField.FieldType.WALL && distances[newRow][newCol] == Integer.MAX_VALUE) {
                        distances[newRow][newCol] = currDistance + 1;
                    if(dir == -1) {
                        prevDirection[newRow][newCol] = i;
                    } else {
                        prevDirection[newRow][newCol] = prevDirection[row][col];
                    }
                    queue.add(new int[]{newRow, newCol, i});
                }
            }
        }
        int[] outputSpeed = new int[3];
        outputSpeed[2] = distances[endRow][endCol];
        // If goal is unreachable.
        if(distances[endRow][endCol] == Integer.MAX_VALUE) {
            outputSpeed[0] = -1;
            outputSpeed[1] = -1;
            return outputSpeed;
        }
        int firstDirection = prevDirection[endRow][endCol];
        // If Entity is already no goal.
        if(firstDirection == -1) {
            System.out.println("SHORTEST PATH PROBLEM");
            return outputSpeed;
        }
        switch(DIRECTIONS[firstDirection]) {
            case "UP":
                outputSpeed[1] = Math.abs(dy + dx)*(-1);
                break;
            case "DOWN":
                outputSpeed[1] = Math.abs(dy + dx);
                break;
            case "LEFT":
                outputSpeed[0] = Math.abs(dy + dx)*(-1);
                break;
            case "RIGHT":
                outputSpeed[0] = Math.abs(dy + dx);
                break;
        }

        return outputSpeed;
    }
//    int ShortestPath(GameField.FieldType[][] matrix, int startRow, int startCol, int endRow, int endCol) {
//        int rows = matrix.length;
//        int cols = matrix[0].length;
//
//        Queue<int[]> queue = new LinkedList<>();
//        queue.add(new int[]{startRow, startCol, 0});
//        while (!queue.isEmpty()) {
//            int[] cell = queue.poll();
//            int row = cell[0];
//            int col = cell[1];
//
//            if(cell[0] == endRow && cell[1] == endCol) {
//                return cell[2];
//            }
//
////            for(int i = 0; i < 4; i++) {
////                int newRow = row + ROW_OFFSETS[i];
////                int newCol = col + COL_OFFSETS[i];
////                if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
////                        matrix[newRow][newCol] != GameField.FieldType.WALL && distances[newRow][newCol] == Integer.MAX_VALUE) {
////                    distances[newRow][newCol] = currDistance + 1;
////                    if (dir == -1) {
////                        prevDirection[newRow][newCol] = i;
////                    } else {
////                        prevDirection[newRow][newCol] = prevDirection[row][col];
////                    }
////                    queue.add(new int[]{newRow, newCol, i});
////                }
////            }
//
//        }
//
//    }
    public static int[] ShortestPathSpeed(Ghost ghost, Player player, GameField gameField, int tileSize) {
        List<int[][]> portalCords = gameField.GetPortalCords();

        int[] output = PathSpeed(gameField.GetGameField(),
                ghost.GetY()/tileSize, ghost.GetX()/tileSize,
                player.GetY()/tileSize, player.GetX()/tileSize,
                        ghost.GetDx(), ghost.GetDy());
        for(int[][] cords : portalCords) {
            int[] firstPartOfPath = PathSpeed(gameField.GetGameField(),
                    ghost.GetY()/tileSize, ghost.GetX()/tileSize,
                    cords[0][0], cords[0][1],
                    ghost.GetDx(), ghost.GetDy());
            int[] secondPartOfPath = PathSpeed(gameField.GetGameField(),
                    cords[1][0], cords[1][1],
                    player.GetY()/tileSize, player.GetX()/tileSize,
                    ghost.GetDx(), ghost.GetDy());

//            System.out.println(firstPartOfPath[2] + " " + secondPartOfPath[2] + "<" + output[2]);
            if(firstPartOfPath[2] + secondPartOfPath[2] < output[2]) {

                output = firstPartOfPath;
            }
        }
        return output;
    }

    public static int[] PinkyPathSpeed(Pinky pinky, Player player, GameField gameField, int tileSize) {
        List<int[][]> portalCords = gameField.GetPortalCords();
        int playerI = pinky.GetY()/tileSize;
        int playerJ = pinky.GetX()/tileSize;
        int rowsNum = gameField.GetRowsNum();
        int colsNum = gameField.GetColsNum();
        if(playerI + 1 < rowsNum && playerJ + 1< colsNum
        && gameField.GetGameField()[playerI][playerJ] != GameField.FieldType.WALL) {
            if(player.GetDy() != 0) {
                playerI = playerI + player.GetDy()/Math.abs(player.GetDy());
            }
            if(player.GetDx() != 0) {
                playerJ = playerJ + player.GetDx()/Math.abs(player.GetDx());
            }
        }

        int[] output = PathSpeed(gameField.GetGameField(),
                pinky.GetY()/tileSize, pinky.GetX()/tileSize,
                playerI, playerJ, pinky.GetDx(), pinky.GetDy());
        for(int[][] cords : portalCords) {
            int[] firstPartOfPath = PathSpeed(gameField.GetGameField(),
                    pinky.GetY()/tileSize, pinky.GetX()/tileSize,
                    cords[0][0], cords[0][1],
                    pinky.GetDx(), pinky.GetDy());
            int[] secondPartOfPath = PathSpeed(gameField.GetGameField(),
                    cords[1][0], cords[1][1],
                    playerI, playerJ,
                    pinky.GetDx(), pinky.GetDy());

//            System.out.println(firstPartOfPath[2] + " " + secondPartOfPath[2] + "<" + output[2]);
            if(firstPartOfPath[2] + secondPartOfPath[2] < output[2]) {
                output = firstPartOfPath;
            }
        }
        return output;
    }

}
