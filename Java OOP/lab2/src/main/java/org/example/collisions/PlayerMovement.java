package org.example.collisions;

import org.example.entities.Player;
import org.example.gameField.GameField;

public class PlayerMovement extends EntityMovement{
    static public boolean IsInputSpeedAllowsToMove(Player player, GameField gameField, int tileSize) {
        int oldDx = player.GetDx();
        int oldDy = player.GetDy();
        player.SetSpeed(player.GetInputDx(), player.GetInputDy());
        boolean isAllows = IsPossibleToMove(player, gameField, tileSize);
        player.SetSpeed(oldDx, oldDy);
        return isAllows;
    }
}
