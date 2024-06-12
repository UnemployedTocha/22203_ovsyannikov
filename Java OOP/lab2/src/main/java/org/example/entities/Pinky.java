package org.example.entities;

import org.example.gameField.GameField;
import org.example.utility.Utility;

import java.util.Timer;
import java.util.TimerTask;

public class Pinky extends Ghost{
    Player player;
    public Pinky(Player player, GameField gameField, int x, int y, int tileSize) {
        super(gameField, x, y, tileSize);
        Timer timer = new Timer();
        dx = 1;
        dy = 0;
        timer.schedule(new TimerTask() {
            @Override
            public void run() {
                isSleeping = false;
            }
        }, 7000);

        this.player = player;
    }

    @Override
    public void UpdateSpeed(GameField gameField) {
        if(hitbox.x / tileSize == (hitbox.x + hitbox.width) / tileSize && hitbox.y / tileSize == (hitbox.y + hitbox.height) / tileSize) {
            int[] speed = Utility.PinkyPathSpeed(this, player, gameField, tileSize);
            dx = speed[0];
            dy = speed[1];
        }
    }
}
