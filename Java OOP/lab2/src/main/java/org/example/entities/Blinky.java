package org.example.entities;

import org.example.gameField.GameField;
import org.example.utility.Utility;

import javax.swing.*;

public class Blinky extends Ghost{
    Player player;
    int resTime = 5000;
    public Blinky(Player player, GameField gameField, int x, int y, int tileSize) {
        super(gameField, x, y, tileSize);
        Timer timer = new Timer(resTime, e -> isSleeping = false);
        timer.setRepeats(false);
        timer.start();
        defaultDx = -1;
        defaultDy = 0;
        dx = 1;
        dy = 0;
//        timer.schedule(new TimerTask() {
//            @Override
//            public void run() {
//                isSleeping = false;
//                System.out.println(isSleeping);
//            }
//        }, 5000);

        this.player = player;
    }

    @Override
    public void UpdateSpeed(GameField gameField) {
        if(hitbox.x / tileSize == (hitbox.x + hitbox.width) / tileSize && hitbox.y / tileSize == (hitbox.y + hitbox.height) / tileSize) {
            int[] speed;
            if(!isScary) {
                speed = Utility.ShortestPathSpeed(this, player, gameField, tileSize);
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
