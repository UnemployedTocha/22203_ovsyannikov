package org.example.entities;

import org.example.gameField.GameField;

import java.sql.Time;
import java.util.Timer;
import java.util.TimerTask;

public abstract class Ghost extends Entity{
    protected boolean isEatable = false;
    protected boolean isScary = false;
    protected int tileSize;
    int defaultDx = 0;
    int defaultDy = -1;
    int respawnX;
    int respawnY;

    Ghost(GameField gameField, int x, int y, int tileSize) {
        super(gameField, tileSize, tileSize);
        dx = 0;
        dy = 0;
        this.x = x;
        this.y = y;
        respawnX = x;
        respawnY = y;
        this.tileSize = tileSize;
    }

    public abstract void UpdateSpeed(GameField gameField);

    public void MakeGhostScary() {
        isScary = true;
        isEatable = true;
        Timer timer = new Timer();
        timer.schedule(new TimerTask() {
            @Override
            public void run() {
                isSleeping = false;
                isScary = false;
            }
        }, 5000);
    }
    public void KillGhost() {
        x = respawnX;
        y = respawnY;
        SetDefaultSpeed();
        isSleeping = true;
        Timer timer = new Timer();
        timer.schedule(new TimerTask() {
            @Override
            public void run() {
                isSleeping = false;
                isScary = false;
            }
        }, 10000);

    }
    void SetDefaultSpeed() {
        dx = defaultDx;
        dy = defaultDy;
    }
}
