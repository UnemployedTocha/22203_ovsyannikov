package org.example.collisions;

import org.example.entities.Entity;
import org.example.gameField.GameField;

public class EntityMovement {
    static protected int[][] GetFrontDots(Entity entity) {
        int nextX1, nextX2;
        int nextY1, nextY2;
        int[][] dotsPair = new int[2][2];

        if(entity.GetDx() > 0) {
            nextX1 = entity.GetX() + entity.GetHitboxWidth();
            nextY1 = entity.GetY();
            nextX2 = nextX1;
            nextY2 = nextY1 + entity.GetHitboxHeight();
        } else if(entity.GetDy() > 0) {
            nextX1 = entity.GetX();
            nextY1 = entity.GetY() + entity.GetHitboxHeight();
            nextX2 = nextX1 + entity.GetHitboxWidth();
            nextY2 = nextY1;
        } else if(entity.GetDy() < 0){
            nextX1 = entity.GetX();
            nextY1 = entity.GetY();
            nextX2 = nextX1 + entity.GetHitboxWidth();
            nextY2 = nextY1;
        } else {
            nextX1 = entity.GetX();
            nextY1 = entity.GetY();
            nextX2 = nextX1;
            nextY2 = nextY1 + entity.GetHitboxHeight();
        }
        dotsPair[0][0] = nextX1;
        dotsPair[0][1] = nextY1;
        dotsPair[1][0] = nextX2;
        dotsPair[1][1] = nextY2;
        return dotsPair;
    }
    static protected int[][] GetNextFrontDots(Entity entity) {
        int[][] dotsPair = GetFrontDots(entity);
        dotsPair[0][0] += entity.GetDx();
        dotsPair[0][1] += entity.GetDy();
        dotsPair[1][0] += entity.GetDx();
        dotsPair[1][1] += entity.GetDy();
        return dotsPair;
    }
    static public boolean IsPossibleToMove(Entity entity, GameField gameField, int tileSize) {
        int[][] dotsPair = GetNextFrontDots(entity);

        return !(gameField.GetGameField()[dotsPair[0][1] / tileSize][dotsPair[0][0] / tileSize].equals(GameField.FieldType.WALL) ||
                gameField.GetGameField()[dotsPair[1][1] / tileSize][dotsPair[1][0] / tileSize].equals(GameField.FieldType.WALL));
    }

    static public GameField.FieldType GetPlayerCell(Entity entity, GameField gameField, int tileSize) {
        GameField.FieldType entityCell = gameField.GetEntityCell(entity);
        int nextX1, nextX2;
        int nextY1, nextY2;
        if(entity.GetDx() > 0) {
            nextX1 = entity.GetX() + entity.GetDx() + entity.GetHitboxWidth();
            nextY1 = entity.GetY() + entity.GetDy();
            nextX2 = nextX1;
            nextY2 = nextY1 + entity.GetHitboxHeight();
        } else if(entity.GetDy() > 0) {
            nextX1 = entity.GetX() + entity.GetDx();
            nextY1 = entity.GetY() + entity.GetDy() + entity.GetHitboxHeight();
            nextX2 = nextX1 + entity.GetHitboxWidth();
            nextY2 = nextY1;
        } else if(entity.GetDy() < 0){
            nextX1 = entity.GetX() + entity.GetDx();
            nextY1 = entity.GetY() + entity.GetDy();
            nextX2 = nextX1 + entity.GetHitboxWidth();
            nextY2 = nextY1;
        } else {
            nextX1 = entity.GetX() + entity.GetDx();
            nextY1 = entity.GetY() + entity.GetDy();
            nextX2 = nextX1;
            nextY2 = nextY1 + entity.GetHitboxHeight();
        }

        if(!gameField.GetGameField()[nextY1 / tileSize][nextX1 / tileSize].equals(entityCell)) {
            return gameField.GetGameField()[nextY1 / tileSize][nextX1 / tileSize];
        } else if(!gameField.GetGameField()[nextY2 / tileSize][nextX2 / tileSize].equals(entityCell)) {
            return gameField.GetGameField()[nextY2 / tileSize][nextX2 / tileSize];
        }
        return entityCell;
    }
}
