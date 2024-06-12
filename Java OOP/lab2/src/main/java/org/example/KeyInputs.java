package org.example;

import org.example.entities.Player;
import org.example.view.GamePanel;

import javax.swing.*;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class KeyInputs implements KeyListener {

    private final Player player;

    public KeyInputs(Player player, GamePanel gamePanel) {
        this.player = player;
    }
    @Override
    public void keyTyped(KeyEvent e) {

    }

    @Override
    public void keyPressed(KeyEvent e) {

        switch(e.getKeyCode()) {
            case KeyEvent.VK_W:
                player.MoveUp();
                break;
            case KeyEvent.VK_S:
                player.MoveDown();
                break;
            case KeyEvent.VK_A:
                player.MoveLeft();
                break;
            case KeyEvent.VK_D:
                player.MoveRight();
                break;
        }
    }

    @Override
    public void keyReleased(KeyEvent e) {

    }
}
// If чё-то там != current key, то надо подменитьб