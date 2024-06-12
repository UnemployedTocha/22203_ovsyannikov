package org.example;

import org.example.collisions.PlayerCollisionWithItems;
import org.example.collisions.PlayerEntityCollision;
import org.example.collisions.PlayerMovement;

import org.example.entities.Ghost;
import org.example.entities.Player;
import org.example.gameField.GameField;
import org.example.view.GamePanel;
import org.example.view.GameWindow;

import java.util.ArrayList;
import java.util.List;

public class Pacman implements Runnable{
    private GamePanel gamePanel;
    private GameWindow gameWindow;
    private GameField gameField;
    private Thread gameThread;
    private final int fpsLimit = 120;
    private final int possibleMissclickTime = 450;


    private Player player;
    private List<Ghost> ghosts;
    public Pacman() {
        ghosts = new ArrayList<>();
        player = new Player(null, tileSize);
        gameField = new GameField(player, ghosts, tileSize);

        gamePanel = new GamePanel(player, ghosts, gameField.GetGameField(), tileSize);

        gamePanel.addKeyListener(new KeyInputs(player, gamePanel));
        gameWindow = new GameWindow(gamePanel);
        gamePanel.setFocusable(true);
        gamePanel.requestFocus();

//        run();
        start();
    }

    public void start() {
        gameThread = new Thread(this);
        gameThread.start();
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
                PlayerCollisionWithItems.CheckPlayerCollisionWithItems(player, gameField, tileSize);
                for(Ghost ghost : ghosts) {
                    boolean flag = PlayerEntityCollision.CheckCollisionWithGhost(player, ghost, gameField.GetGameField(), tileSize);
                    if(flag) {
                        ghost.MakeGhostScary();
                        ghost.KillGhost();
                    }
                }
                gamePanel.repaint();
                frameTime = System.currentTimeMillis();
            }
        }


    }


    final int tileSize = 24;
    final int maxWindowCol = 31;
    final int maxWindowRow = 28;
    final int windowWidth = maxWindowCol * tileSize;
    final int windowHeight = maxWindowRow * tileSize;
}





/*

    if(System.currentTimeMillis() - lastCheck >= 1000) {
        lastCheck = System.currentTimeMillis();
        System.out.println("FPS: " + frames);
        frames = 0;
    }

 */