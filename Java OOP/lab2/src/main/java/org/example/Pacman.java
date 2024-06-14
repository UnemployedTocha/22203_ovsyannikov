package org.example;

import org.example.collisions.PlayerCollisions;
import org.example.collisions.PlayerMovement;

import org.example.entities.Ghost;
import org.example.entities.Player;
import org.example.gameField.GameField;
import org.example.view.ButtonClickListener;
import org.example.view.GamePanel;
import org.example.view.GameWindow;
import org.example.view.ScorePanel;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.List;

public class Pacman implements Runnable {
    private GamePanel gamePanel;
    private ScorePanel scorePanel;
    private JPanel cardPanel;
    private GameField gameField;
    private GameWindow gameWindow;
    private final int fpsLimit = 120;
    private final int possibleMissclickTime = 450;


    private Player player;
    private List<Ghost> ghosts;
    public Pacman() {
        ghosts = new ArrayList<>();
        player = new Player(null, tileSize);
        gameField = new GameField(player, ghosts, tileSize);

        scorePanel = new ScorePanel(player, gameField, ghosts);
        gamePanel = new GamePanel(player, ghosts, gameField.GetGameField(), tileSize);
        cardPanel = new JPanel(new CardLayout());
        cardPanel.add(gamePanel, "gamePanel");
        cardPanel.add(scorePanel, "scorePanel");

        gamePanel.addKeyListener(new KeyInputs(player, gamePanel));
        gameWindow = new GameWindow(cardPanel, gameField, player, ghosts, gamePanel);
        scorePanel.setButtonClickListener(gameWindow);
        gamePanel.setFocusable(true);
        gamePanel.requestFocus();

        run();
    }

    @Override
    public void run() {
        double eachFrameTime = 1000.0 / fpsLimit;
        long frameTime = System.currentTimeMillis();
        long lastCheck = System.currentTimeMillis();
        double frames = 0;
        while(true) {
            if(System.currentTimeMillis() - frameTime >= eachFrameTime) {
                if (PlayerMovement.IsInputSpeedAllowsToMove(player, gameField, tileSize) &&
                    (System.currentTimeMillis() - player.GetLastInputTime() <= possibleMissclickTime)) {
                    player.SetInputSpeedAsActual();
                    player.Update();

                } else if(PlayerMovement.IsPossibleToMove(player, gameField, tileSize)) {
                    player.Update();
                }
                ++frames;

                if(System.currentTimeMillis() - lastCheck >= 1000) {
                    lastCheck = System.currentTimeMillis();
                    System.out.println("FPS: " + frames);
                    frames = 0;
                }

                gameField.update(ghosts);
                boolean isPlayerDead = PlayerCollisions.CheckPlayerCollisions(gameField, player, ghosts, tileSize);
                gamePanel.repaint();
                scorePanel.repaint();
                frameTime = System.currentTimeMillis();
                if(gameField.isLevelCompleted()) {
                    gameWindow.SwitchToScoreBoard();
                }
                if(isPlayerDead && player.GetLifesNum() == 0) {
                    gameField.GlobalLevelRestart(player, ghosts);
                } else if(isPlayerDead){
                    gameField.LocalRestart(player, ghosts);
                }

            }

        }
    }


    final int tileSize = 24;

//    @Override
//    public void onButtonClick() {
//        gameField = new GameField(player, ghosts, tileSize);
//    }
}





/*

    if(System.currentTimeMillis() - lastCheck >= 1000) {
        lastCheck = System.currentTimeMillis();
        System.out.println("FPS: " + frames);
        frames = 0;
    }

 */