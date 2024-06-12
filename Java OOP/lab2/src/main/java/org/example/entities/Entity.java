package org.example.entities;

import org.example.gameField.GameField;

import java.awt.*;

public abstract class Entity {
    protected int x = 0;
    protected int y = 0;
    protected int dx = 0;
    protected int dy = 0;
    protected int width;
    protected int height;
    protected int tileSize;
    boolean isSleeping = true;
    GameField gameField;
    protected Rectangle hitbox;
    void SetHitbox() {
        hitbox = new Rectangle();
        hitbox.x = x;
        hitbox.y = y;
        hitbox.width = width - 1;
        hitbox.height = height - 1;
    }
    public Entity(GameField gameField, int width, int height){
        this.width = width;
        this.height = height;
        this.gameField = gameField;
        tileSize = Math.max(width, height);
        SetHitbox();
    }
    public void SetSpeed(int dx, int dy) {
        this.dx = dx;
        this.dy = dy;
    }

    public void Update() {
        if(isSleeping) {
            return;
        }
        x += dx;
        y += dy;
        hitbox.x = x;
        hitbox.y = y;

        if  (hitbox.x / tileSize == ((hitbox.x + hitbox.width) / tileSize)
            && hitbox.y / tileSize == (hitbox.y + hitbox.height) / tileSize
            && gameField.GetEntityCell(this) == GameField.FieldType.PORTAL){
            if(dx != 0) {
                x = (x + tileSize * (dx / Math.abs(dx))) % (tileSize * gameField.GetColsNum()) + (dx / Math.abs(dx));
                if(x < 0) {
                    x += (tileSize * gameField.GetColsNum());
                }
            } else {
                y = (y + tileSize * (dy / Math.abs(dy))) % (tileSize * gameField.GetRowsNum()) + (dx / Math.abs(dx));
                if(y < 0) {
                    y += (tileSize * gameField.GetRowsNum());
                }
            }
            hitbox.x = x;
            hitbox.y = y;
        }
    }
    public int GetX() {
        return x;
    }
    public int GetY() {
        return y;
    }
    public void SetX(int x) {this.x = x; }
    public void SetY(int y) {this.y = y; }
    public int GetDx() { return dx; }
    public int GetDy() { return dy; }
    public int GetHeight() {
        return height;
    }
    public int GetHitboxX() {
        return hitbox.x;
    }
    public int GetHitboxY() {
        return hitbox.y;
    }
    public int GetHitboxHeight() {
        return hitbox.height;
    }
    public int GetHitboxWidth() {
        return hitbox.width;
    }
    public int GetWidth() {
        return width;
    }
    public void MoveUp() {
        dy = Math.abs(dy + dx)*(-1);
        dx = 0;
    }
    public void MoveDown() {
        dy = Math.abs(dy + dx);
        dx = 0;
    }
    public void MoveLeft() {
        dx = Math.abs(dy + dx)*(-1);
        dy = 0;
    }
    public void MoveRight() {
        dx = Math.abs(dy + dx);
        dy = 0;
    }

}
