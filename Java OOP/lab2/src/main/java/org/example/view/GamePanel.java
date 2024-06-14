package org.example.view;

import java.io.IOException;
import java.util.List;

import org.example.entities.Blinky;
import org.example.entities.Pinky;
import org.example.entities.Inky;
import org.example.entities.Clyde;
import org.example.entities.Ghost;
import org.example.entities.Player;
import org.example.gameField.GameField;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.InputStream;

enum Dir {
    UP(2),
    RIGHT(0),
    LEFT(1),
    DOWN(3);
    private final int value;
    Dir(int value) {
        this.value = value;
    }
    int GetValue() {
        return value;
    }
}
public class GamePanel extends JPanel {
    private int ticks = 0;
    private final int ticksPerAnimation = 12;
    private int pacmanAnimationIndex = 0;
    private BufferedImage wallPic;
    private BufferedImage[][] pacmanAssets;
    private BufferedImage[] blinkyAssets;
    private BufferedImage[] pinkyAssets;
    private BufferedImage[] inkyAssets;
    private BufferedImage[] clydeAssets;
    private BufferedImage[] pacmanPic;
    private BufferedImage scaryGhostPic;
    private BufferedImage coinPic;
    private BufferedImage cherryPic;
    private BufferedImage blinkyPic;
    private BufferedImage pinkyPic;
    private BufferedImage inkyPic;
    private BufferedImage clydePic;
    private BufferedImage heartPic;
    private Player player;
    private List<Ghost> ghosts;
    private GameField.FieldType[][] gameField;
    int tileSize;
    final int maxWindowCol;
    final int maxWindowRow;
    final int windowWidth;
    final int windowHeight;


    private BufferedImage ImportAsset(String path) {
        InputStream in = GamePanel.class.getClassLoader().getResourceAsStream(path);
        BufferedImage img = null;
        assert in != null;
        try {
            img = ImageIO.read(in);
        } catch (IOException ex) {
            System.out.println(ex.getMessage());
        }
        return img;
    }
    private void ImportAssets() {
        pacmanPic = new BufferedImage[3];
        pacmanAssets = new BufferedImage[4][3];
        blinkyAssets = new BufferedImage[4];
        pinkyAssets = new BufferedImage[4];
        inkyAssets = new BufferedImage[4];
        clydeAssets = new BufferedImage[4];

        wallPic = ImportAsset("Wall.png");
        pacmanPic[0] = ImportAsset("Pacman1.png");
        pacmanPic[1] = ImportAsset("Pacman2.png");
        pacmanPic[2] = ImportAsset("Pacman3.png");
        blinkyPic = ImportAsset("Blinky/BlinkyUp.png");
        pinkyPic = ImportAsset("Pinky/PinkyUp.png");
        inkyPic = ImportAsset("Inky/InkyUp.png");
        clydePic =  ImportAsset("Clyde/ClydeUp.png");

        pacmanAssets[Dir.RIGHT.GetValue()][0] = pacmanPic[0];
        pacmanAssets[Dir.LEFT.GetValue()][0] = pacmanPic[0];
        pacmanAssets[Dir.DOWN.GetValue()][0] = pacmanPic[0];
        pacmanAssets[Dir.UP.GetValue()][0] = pacmanPic[0];

        blinkyAssets[Dir.RIGHT.GetValue()] = ImportAsset("Blinky/BlinkyRight.png");
        pinkyAssets[Dir.RIGHT.GetValue()] = ImportAsset("Pinky/PinkyRight.png");
        inkyAssets[Dir.RIGHT.GetValue()] = ImportAsset("Inky/InkyRight.png");
        clydeAssets[Dir.RIGHT.GetValue()] = ImportAsset("Clyde/ClydeRight.png");

        pacmanAssets[0][1] = pacmanPic[1];
        pacmanAssets[0][2] = pacmanPic[2];

        pacmanAssets[Dir.LEFT.GetValue()][1] = ImportAsset("Pacman2_Left.png");
        pacmanAssets[Dir.LEFT.GetValue()][2] = ImportAsset("Pacman3_Left.png");
        blinkyAssets[Dir.LEFT.GetValue()] = ImportAsset("Blinky/BlinkyLeft.png");
        pinkyAssets[Dir.LEFT.GetValue()] = ImportAsset("Pinky/PinkyLeft.png");
        inkyAssets[Dir.LEFT.GetValue()] = ImportAsset("Inky/InkyLeft.png");
        clydeAssets[Dir.LEFT.GetValue()] =  ImportAsset("Clyde/ClydeLeft.png");

        pacmanAssets[Dir.UP.GetValue()][1] = ImportAsset("Pacman2_Up.png");
        pacmanAssets[Dir.UP.GetValue()][2] = ImportAsset("Pacman3_Up.png");
        blinkyAssets[Dir.UP.GetValue()] = ImportAsset("Blinky/BlinkyUp.png");
        pinkyAssets[Dir.UP.GetValue()] = ImportAsset("Pinky/PinkyUp.png");
        inkyAssets[Dir.UP.GetValue()] = ImportAsset("Inky/InkyUp.png");
        clydeAssets[Dir.UP.GetValue()] =  ImportAsset("Clyde/ClydeUp.png");

        pacmanAssets[Dir.DOWN.GetValue()][1] = ImportAsset("Pacman2_Down.png");
        pacmanAssets[Dir.DOWN.GetValue()][2] = ImportAsset("Pacman3_Down.png");
        blinkyAssets[Dir.DOWN.GetValue()] = ImportAsset("Blinky/BlinkyDown.png");
        pinkyAssets[Dir.DOWN.GetValue()] = ImportAsset("Pinky/PinkyDown.png");
        inkyAssets[Dir.DOWN.GetValue()] = ImportAsset("Inky/InkyDown.png");
        clydeAssets[Dir.DOWN.GetValue()] =  ImportAsset("Clyde/ClydeDown.png");

        coinPic = ImportAsset("Dot.png");
        cherryPic = ImportAsset("Fruit.png");
        scaryGhostPic = ImportAsset("EatableGhost/EatableGhost.png");
        heartPic = ImportAsset("Heart.png");
    }
    public GamePanel(Player player, List<Ghost> ghosts, GameField.FieldType[][] gameField, int tileSize) {
        this.tileSize = tileSize;
        maxWindowRow = gameField.length;
        maxWindowCol = gameField[0].length;
        windowWidth = maxWindowCol * tileSize;
        windowHeight = maxWindowRow * tileSize;

        ImportAssets();
        setBackground(Color.BLACK);
        this.player = player;
        this.gameField = gameField;
        this.ghosts = ghosts;
        setPreferredSize(new Dimension(windowWidth, windowHeight));
    }

    public void PaintField(Graphics g) {
        for(int i = 0; i < gameField.length; ++i) {
            for(int j = 0; j < gameField[i].length; ++j) {
                if (gameField[i][j].equals(GameField.FieldType.WALL)) {
                    g.drawImage(wallPic,j*tileSize, i*tileSize, tileSize, tileSize, null);
                } else if(gameField[i][j].equals(GameField.FieldType.BLOCK_WITH_COINS)) {
                    g.drawImage(coinPic,j*tileSize + tileSize/3 , i*tileSize + tileSize/3, tileSize/3, tileSize/3, null);
                } else if(gameField[i][j].equals(GameField.FieldType.FRUIT)) {
//                    g.drawImage(cherryPic,j*tileSize, i*tileSize, tileSize, tileSize, null);
                } else if(gameField[i][j].equals(GameField.FieldType.POWER_PELLET)) {
                    g.drawImage(cherryPic,j*tileSize , i*tileSize, tileSize, tileSize, null);
                }

            }
        }
    }
    void PaintGhosts(Graphics g) {
        for(Ghost ghost : ghosts) {
            if(ghost.IsScary()) {
                g.drawImage(scaryGhostPic, ghost.GetX() , ghost.GetY(), tileSize, tileSize, null);
            } else if(ghost instanceof Blinky) {
                blinkyPic = RotateGhosts(ghost, blinkyAssets);
                g.drawImage(blinkyPic, ghost.GetX() , ghost.GetY(), tileSize, tileSize, null);
            } else if(ghost instanceof Pinky) {
                pinkyPic = RotateGhosts(ghost, pinkyAssets);
                g.drawImage(pinkyPic, ghost.GetX() , ghost.GetY(), tileSize, tileSize, null);
            } else if(ghost instanceof Inky) {
                inkyPic = RotateGhosts(ghost, inkyAssets);
                g.drawImage(inkyPic, ghost.GetX() , ghost.GetY(), tileSize, tileSize, null);
            } else if(ghost instanceof Clyde) {
                clydePic = RotateGhosts(ghost, clydeAssets);
                g.drawImage(clydePic, ghost.GetX() , ghost.GetY(), tileSize, tileSize, null);
            }


        }
    }
    private void UpdateAnimation() {
        ++ticks;
        if(ticks >= ticksPerAnimation) {
            ticks = 0;
            pacmanAnimationIndex = (pacmanAnimationIndex + 1) % pacmanPic.length;
        }
    }
    public BufferedImage RotateGhosts(Ghost ghost, BufferedImage[] entityAssets) {
        if(ghost.GetDx() > 0) {
            return entityAssets[Dir.RIGHT.GetValue()];
        } else if(ghost.GetDx() < 0) {
            return entityAssets[Dir.LEFT.GetValue()];
        } else if(ghost.GetDy() > 0) {
            return entityAssets[Dir.DOWN.GetValue()];
        } else {
            return entityAssets[Dir.UP.GetValue()];
        }

    }
    public void RotatePlayer(int dx, int dy) {
        if(dx > 0) {
            System.arraycopy(pacmanAssets[0], 0, pacmanPic, 0, pacmanPic.length);
        } else if(dx < 0) {
            System.arraycopy(pacmanAssets[1], 0, pacmanPic, 0, pacmanPic.length);
        } else if(dy > 0) {
            System.arraycopy(pacmanAssets[3], 0, pacmanPic, 0, pacmanPic.length);
        } else {
            System.arraycopy(pacmanAssets[2], 0, pacmanPic, 0, pacmanPic.length);
        }
    }
    public void DrawLifes(Graphics g) {
        for(int i = 0; i < player.GetLifesNum(); ++i) {
            g.drawImage(heartPic, windowWidth - (i + 1)*tileSize, windowHeight - tileSize, tileSize, tileSize, null);
        }
    }
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        PaintField(g);
        PaintGhosts(g);
        RotatePlayer(player.GetDx(), player.GetDy());
        g.drawImage(pacmanPic[pacmanAnimationIndex],player.GetX(), player.GetY(), player.GetHeight(), player.GetWidth(), null);
        DrawLifes(g);
        UpdateAnimation();

    }

}
