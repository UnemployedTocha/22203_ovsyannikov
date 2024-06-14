package org.example.view;

import org.example.entities.Ghost;
import org.example.entities.Player;
import org.example.gameField.GameField;

import javax.swing.*;
import java.awt.*;
import java.util.List;


public class GameWindow implements ButtonClickListener{
    private JPanel cardPanel;
    private CardLayout cardLayout;
    private GameField gameField;
    private Player player;
    private JPanel gamePanel;
    private List<Ghost> ghosts;
    public GameWindow(JPanel cardPanel, GameField gameField, Player player, List<Ghost> ghosts, JPanel gamePanel) {
        JFrame window = new JFrame("Pacman");
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.cardPanel = cardPanel;
        this.gameField = gameField;
        this.ghosts = ghosts;
        this.player = player;
        this.gamePanel = gamePanel;
        window.add(cardPanel);
        window.setBackground(Color.BLACK);
        window.pack();
        window.setResizable(false);

        window.setLocationRelativeTo(null);

        cardLayout = (CardLayout) (cardPanel.getLayout());
        cardLayout.show(cardPanel, "gamePanel");

        window.setVisible(true);
    }

    public void SwitchToScoreBoard() {
        cardLayout.show(cardPanel, "scorePanel");
    }
    public void SwitchToGamePanel() {
        cardLayout.show(cardPanel, "gamePanel");
        gamePanel.requestFocus();
    }

    @Override
    public void onButtonClick() {
        gameField.GlobalLevelRestart(player, ghosts);
        SwitchToGamePanel();
    }
}