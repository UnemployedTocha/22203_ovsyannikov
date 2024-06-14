package org.example.utility;

import org.example.entities.*;
import org.example.gameField.GameField;

import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

public class Utility {
    private static final int[] ROW_OFFSETS = {-1, 0, 1, 0};
    private static final int[] COL_OFFSETS = {0, 1, 0, -1};

    // ENUM
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
        // If Entity is already on goal.
        if(firstDirection == -1) {
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
        int playerI = player.GetY()/tileSize;
        int playerJ = player.GetX()/tileSize;
        int ghostGoalI;
        int ghostGoalJ;
        int rowsNum = gameField.GetRowsNum();
        int colsNum = gameField.GetColsNum();

        if(player.GetDy() != 0) {
            ghostGoalI = playerI +  (player.GetDy()/Math.abs(player.GetDy()));
            ghostGoalJ = playerJ;
        } else {
            ghostGoalI = playerI;
            ghostGoalJ = playerJ + (player.GetDx()/Math.abs(player.GetDx()));
        }

        if(ghostGoalI < rowsNum && ghostGoalJ < colsNum && ghostGoalI >= 0 && ghostGoalJ >= 0
            && gameField.GetGameField()[ghostGoalI][ghostGoalJ] != GameField.FieldType.WALL) {
            playerI = ghostGoalI;
            playerJ = ghostGoalJ;
        }

        int[] output = PathSpeed(gameField.GetGameField(),
                pinky.GetY()/tileSize, pinky.GetX()/tileSize,
                playerI, playerJ, pinky.GetDx(), pinky.GetDy());
        if(output[0] == 0 && output[1] == 0) {
            output = PathSpeed(gameField.GetGameField(),
                    pinky.GetY()/tileSize, pinky.GetX()/tileSize,
                    player.GetY()/tileSize, player.GetX()/tileSize, pinky.GetDx(), pinky.GetDy());
        }
        for(int[][] cords : portalCords) {
            int[] firstPartOfPath = PathSpeed(gameField.GetGameField(),
                    pinky.GetY()/tileSize, pinky.GetX()/tileSize,
                    cords[0][0], cords[0][1],
                    pinky.GetDx(), pinky.GetDy());
            int[] secondPartOfPath = PathSpeed(gameField.GetGameField(),
                    cords[1][0], cords[1][1],
                    playerI, playerJ,
                    pinky.GetDx(), pinky.GetDy());

            if(firstPartOfPath[2] + secondPartOfPath[2] < output[2]) {
                output = firstPartOfPath;
            }
        }
        return output;
    }

    public static int[] InkyPathSpeed(Inky inky, Player player, GameField gameField, int tileSize) {
        List<int[][]> portalCords = gameField.GetPortalCords();
        int playerI = player.GetY()/tileSize;
        int playerJ = player.GetX()/tileSize;
        int ghostGoalI;
        int ghostGoalJ;
        int rowsNum = gameField.GetRowsNum();
        int colsNum = gameField.GetColsNum();

        if(player.GetDy() != 0) {
            ghostGoalI = playerI - (player.GetDy()/Math.abs(player.GetDy()));
            ghostGoalJ = playerJ;
        } else {
            ghostGoalI = playerI;
            ghostGoalJ = playerJ - (player.GetDx()/Math.abs(player.GetDx()));
        }

        if(ghostGoalI < rowsNum && ghostGoalJ < colsNum && ghostGoalI >= 0 && ghostGoalJ >= 0
                && gameField.GetGameField()[ghostGoalI][ghostGoalJ] != GameField.FieldType.WALL) {
            playerI = ghostGoalI;
            playerJ = ghostGoalJ;
        }

        int[] output = PathSpeed(gameField.GetGameField(),
                inky.GetY()/tileSize, inky.GetX()/tileSize,
                playerI, playerJ, inky.GetDx(), inky.GetDy());
        if(output[0] == 0 && output[1] == 0) {
            output = PathSpeed(gameField.GetGameField(),
                    inky.GetY()/tileSize, inky.GetX()/tileSize,
                    player.GetY()/tileSize, player.GetX()/tileSize, inky.GetDx(), inky.GetDy());
        }
        for(int[][] cords : portalCords) {
            int[] firstPartOfPath = PathSpeed(gameField.GetGameField(),
                    inky.GetY()/tileSize, inky.GetX()/tileSize,
                    cords[0][0], cords[0][1],
                    inky.GetDx(), inky.GetDy());
            int[] secondPartOfPath = PathSpeed(gameField.GetGameField(),
                    cords[1][0], cords[1][1],
                    playerI, playerJ,
                    inky.GetDx(), inky.GetDy());

            if (firstPartOfPath[2] + secondPartOfPath[2] < output[2]
                && (firstPartOfPath[0] != 0 || firstPartOfPath[1] != 0
                    && (secondPartOfPath[0] != 0 || secondPartOfPath[1] != 0))) {
                output = firstPartOfPath;
            }
        }
        return output;
    }
    public static int[] ClydePathSpeed(Clyde clyde, Player player, GameField gameField, int tileSize) {
        int playerI = player.GetY()/tileSize;
        int playerJ = player.GetX()/tileSize;

        int[] output = PathSpeed(gameField.GetGameField(),
                clyde.GetY()/tileSize, clyde.GetX()/tileSize,
                playerI, playerJ, clyde.GetDx(), clyde.GetDy());

        return output;
    }
    public static int[] ScaryGhostPathSpeed(Ghost ghost, Player player, GameField gameField, int tileSize) {
        int[] output = new int[2];
        int dir = (int)(Math.random() * 4);
        int newI = (ghost.GetY()/tileSize) + ROW_OFFSETS[dir];
        int newJ = (ghost.GetX()/tileSize) + COL_OFFSETS[dir];
        while(true) {
            if(newI >= 0 && newJ >= 0 && GameField.FieldType.WALL != gameField.GetGameField()[newI][newJ]
                    && newI < gameField.GetRowsNum() && newJ < gameField.GetColsNum()) {
                if(newI > (ghost.GetY()/tileSize)) {
                    output[1] = Math.abs(ghost.GetDx() + ghost.GetDy());
                } else if((newI < (ghost.GetY()/tileSize))) {
                    output[1] = (-1)*Math.abs(ghost.GetDx() + ghost.GetDy());
                } else if(newJ > (ghost.GetX()/tileSize)) {
                    output[0] = Math.abs(ghost.GetDx() + ghost.GetDy());
                } else {
                   output[0] = (-1)*Math.abs(ghost.GetDx() + ghost.GetDy());
                }
                break;
            }
            System.out.println("ABOBA");
            dir += 1;
            dir %= 4;
            newI = (ghost.GetY()/tileSize) + ROW_OFFSETS[dir];
            newJ = (ghost.GetX()/tileSize) + COL_OFFSETS[dir];
        }
        return output;
    }
}
