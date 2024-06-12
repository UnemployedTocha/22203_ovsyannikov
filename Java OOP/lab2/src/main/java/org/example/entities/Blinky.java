package org.example.entities;

import org.example.gameField.GameField;
import org.example.utility.Utility;

import java.util.Timer;
import java.util.TimerTask;

public class Blinky extends Ghost{
    Player player;
    public Blinky(Player player, GameField gameField, int x, int y, int tileSize) {
        super(gameField, x, y, tileSize);
        Timer timer = new Timer();
        defaultDx = -1;
        defaultDy = 0;
        dx = 1;
        dy = 0;
        timer.schedule(new TimerTask() {
            @Override
            public void run() {
                isSleeping = false;
                System.out.println(isSleeping);
            }
        }, 5000);

        this.player = player;
    }
    private void CalcNewWay() {
        GameField.FieldType[][] arr = gameField.GetGameField();
        int playerI = player.GetX() / tileSize;
        int playerJ = player.GetY() / tileSize;
        int ghostI = x / tileSize;
        int ghostJ = y / tileSize;


    }

    @Override
    public void UpdateSpeed(GameField gameField) {
        if(hitbox.x / tileSize == (hitbox.x + hitbox.width) / tileSize && hitbox.y / tileSize == (hitbox.y + hitbox.height) / tileSize) {
            int[] speed = Utility.ShortestPathSpeed(this, player, gameField, tileSize);
            dx = speed[0];
            dy = speed[1];
        }
    }
}
