package org.example.collisions;

import org.example.entities.Ghost;
import org.example.entities.Player;
import org.example.gameField.GameField;

import java.util.List;

public class PlayerCollisionWithItems extends EntityMovement{
    static public void CheckPlayerCollisionWithItems(Player player, GameField gameField, List<Ghost> ghosts, int tileSize) {
    int[][] dotPairs = GetFrontDots(player);
    int x1 = dotPairs[0][0];
    int x2 = dotPairs[1][0];
    int y1 = dotPairs[0][1];
    int y2 = dotPairs[1][1];
    if (gameField.GetGameField()[y1 / tileSize][x1 / tileSize].equals(GameField.FieldType.BLOCK_WITH_COINS) &&
        gameField.GetGameField()[y2 / tileSize][x2 / tileSize].equals(GameField.FieldType.BLOCK_WITH_COINS)) {
            PlayerCoinCollision(player, gameField, tileSize);
    } else if(gameField.GetGameField()[y1 / tileSize][x1 / tileSize].equals(GameField.FieldType.POWER_PELLET) &&
            gameField.GetGameField()[y2 / tileSize][x2 / tileSize].equals(GameField.FieldType.POWER_PELLET)) {
        gameField.CollectPowerPellet(y1 / tileSize, x1 / tileSize);
        for(Ghost ghost : ghosts) {
            ghost.MakeGhostScary();
        }
    }

    }

    static private void PlayerCoinCollision(Player player, GameField gameField, int tileSize) {
        int[][] frontDots = GetFrontDots(player);
        int x1 = frontDots[0][0];
        int x2 = frontDots[1][0];
        int y1 = frontDots[0][1];
        int y2 = frontDots[1][1];

        int coinX1;
        int coinY1;
        int coinX2;
        int coinY2;

        if(player.GetDx() > 0 || player.GetDy() > 0) {
            coinX1 = (x1 / tileSize) * tileSize + tileSize / 2 + tileSize / 4;
            coinY1 = (y1 / tileSize) * tileSize + tileSize / 2 + tileSize / 4;
            coinX2 = coinX1 + tileSize / 4;
            coinY2 = coinY1 + tileSize / 4;
        } else {
            coinX1 = (x1 / tileSize) * tileSize - tileSize / 2 + tileSize / 4;
            coinY1 = (y1 / tileSize) * tileSize - tileSize / 2 + tileSize / 4;
            coinX2 = coinX1 + tileSize / 4;
            coinY2 = coinY1 + tileSize / 4;
        }

        if ((x1 >= coinX1 && x1 <= coinX2) && (y1 >= coinY1 && y1 <= coinY2) ||
            (x2 >= coinX1 && x2 <= coinX2) && (y2 >= coinY1 && y2 <= coinY2)) {
            gameField.CollectCoin(y1 / tileSize, x1 / tileSize);
            player.UpdateScoresByCollectingCoin();
        }
    }
}
