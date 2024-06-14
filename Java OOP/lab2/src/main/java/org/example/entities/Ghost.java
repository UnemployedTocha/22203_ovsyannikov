package org.example.entities;

import org.example.gameField.GameField;

import javax.swing.Timer;

public abstract class Ghost extends Entity{
    int resTime = 5000;
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

    public boolean IsScary() {
        return isScary;
    }
    public void MakeGhostScary() {
        isScary = true;
        isEatable = true;
        Timer timer = new Timer(7000, e -> {isScary = false; isEatable = false;});
        timer.setRepeats(false);
        timer.start();
    }
    public void KillGhost() {
        x = respawnX;
        y = respawnY;
        SetDefaultSpeed();
        isSleeping = true;
        isScary = false;
        Timer timer = new Timer(8000, e -> {
            isSleeping = false;
        });
        timer.setRepeats(false);
        timer.start();
    }


    public abstract void RespawnGhost();

    void SetDefaultSpeed() {
        dx = defaultDx;
        dy = defaultDy;
    }
}
