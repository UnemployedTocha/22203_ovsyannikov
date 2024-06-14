package org.example.collisions;

import org.example.entities.Ghost;
import org.example.entities.Player;
import org.example.gameField.GameField;

import java.util.List;

public class PlayerCollisions {
    public static boolean CheckPlayerCollisions(GameField gameField, Player player, List<Ghost> ghosts, int tileSize) {
        PlayerCollisionWithItems.CheckPlayerCollisionWithItems(player, gameField, ghosts, tileSize);
        for (Ghost ghost : ghosts) {
            boolean flag = PlayerEntityCollision.CheckCollisionWithGhost(player, ghost, gameField.GetGameField(), tileSize);
            if (flag) {
                if (ghost.IsScary()) {
                    ghost.KillGhost();
                    player.UpdateScoresByKillingGhost();
                } else {
                    return true;
                }
            }
        }
        return false;
    }
}
