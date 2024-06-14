package org.example.entities;

import org.example.gameField.GameField;
import org.example.utility.Utility;

import javax.swing.Timer;

public class Pinky extends Ghost{
    Player player;
    int resTime = 7000;
    public Pinky(Player player, GameField gameField, int x, int y, int tileSize) {
        super(gameField, x, y, tileSize);
        dx = 1;
        dy = 0;
        Timer timer = new Timer(resTime, e -> isSleeping = false);
        timer.setRepeats(false);
        timer.start();

        this.player = player;
    }

    @Override
    public void UpdateSpeed(GameField gameField) {
        if(hitbox.x / tileSize == (hitbox.x + hitbox.width) / tileSize && hitbox.y / tileSize == (hitbox.y + hitbox.height) / tileSize) {
            int[] speed;
            if(!isScary) {
                speed = Utility.PinkyPathSpeed(this, player, gameField, tileSize);
            } else {
                speed = Utility.ScaryGhostPathSpeed(this,  player, gameField, tileSize);
            }
            dx = speed[0];
            dy = speed[1];
        }
    }

    @Override
    public void RespawnGhost(){
        x = respawnX;
        y = respawnY;
        SetDefaultSpeed();
        isSleeping = true;
        isScary = false;
        Timer timer = new Timer(resTime, e -> {
            isSleeping = false;
        });
        timer.setRepeats(false);
        timer.start();
    }
}
