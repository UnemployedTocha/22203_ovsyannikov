package org.example.view;

import org.example.entities.Ghost;
import org.example.entities.Player;
import org.example.gameField.GameField;


import java.util.List;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ScorePanel extends JPanel {
    private Player player;
    List<Ghost> ghosts;
    ButtonClickListener buttonClickListener;
    private int score = 0;
    private JButton restartButton;
    private JLabel scoreLabel;
    public ScorePanel(Player player, GameField gameField, List<Ghost> ghosts) {
        this.player = player;
        this.ghosts = ghosts;
        setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));

        scoreLabel = new JLabel("Score: " + score);
        scoreLabel.setFont(new Font("Serif", Font.BOLD, 36));
        scoreLabel.setForeground(Color.yellow);
        scoreLabel.setAlignmentX(Component.CENTER_ALIGNMENT);
        add(scoreLabel);

        // Отступ
        add(Box.createRigidArea(new Dimension(0, 20)));
        setBackground(Color.BLACK);
        restartButton = new JButton("Restart");
        restartButton.setFont((new Font("Serif", Font.PLAIN, 32)));
        restartButton.setBackground(Color.red);
        restartButton.setAlignmentX(Component.CENTER_ALIGNMENT);
        restartButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (buttonClickListener != null) {
                    buttonClickListener.onButtonClick();
                }
            }
        });
        add(restartButton);
    }

    public void setButtonClickListener(ButtonClickListener buttonClickListener) {
        this.buttonClickListener = buttonClickListener;
    }

    public void paintComponent(Graphics g) {

        scoreLabel.setText("Score: " + player.GetScores());
        score = player.GetScores();
        super.paintComponent(g);
    }
}
