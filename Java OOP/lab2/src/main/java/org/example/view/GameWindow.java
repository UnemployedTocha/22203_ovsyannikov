package org.example.view;

import javax.swing.*;
import java.awt.*;


public class GameWindow {
    public GameWindow(GamePanel gamePanel) {
        JFrame window = new JFrame("Pacman");
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        window.add(gamePanel);
        window.setBackground(Color.BLACK);
        window.pack();
        window.setResizable(false);

        window.setLocationRelativeTo(null);
        window.setVisible(true);
    }
}
