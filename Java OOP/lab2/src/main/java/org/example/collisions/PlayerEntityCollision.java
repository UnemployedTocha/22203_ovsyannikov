package org.example.collisions;

import org.example.entities.Entity;
import org.example.entities.Ghost;
import org.example.entities.Player;
import org.example.gameField.GameField;

public class PlayerEntityCollision extends  EntityMovement {
    static public boolean CheckCollisionWithGhost(Player player, Ghost ghost, GameField.FieldType[][] gameField, int tileSize) {
        int[][] playerFrontDots = GetFrontDots(player);
        int playerX1 = playerFrontDots[0][0];
        int playerX2 = playerFrontDots[1][0];
        int playerY1 = playerFrontDots[0][1];
        int playerY2 = playerFrontDots[1][1];
        int[][] entityFrontDots = GetFrontDots(ghost);
        int entityX1 = entityFrontDots[0][0];
        int entityX2 = entityFrontDots[1][0];
        int entityY1 = entityFrontDots[0][1];
        int entityY2 = entityFrontDots[1][1];

        if(playerY1/tileSize == entityY1/tileSize && playerX1/tileSize == entityX1/tileSize
        && playerY2/tileSize == entityY2/tileSize && playerX2/tileSize == entityX2/tileSize) {
            return true;
        }
        return false;
    }
}
