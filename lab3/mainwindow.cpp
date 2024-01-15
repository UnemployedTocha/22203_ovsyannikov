#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "winwidget.h"


#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QInputDialog>
#include <QString>
#include <QDebug>

MainWindow::MainWindow(QMainWindow *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setFocusPolicy(Qt::StrongFocus);
    ui->setupUi(this);
    scene = new QGraphicsScene(0, 0, ui->graphicsView->width(), ui->graphicsView->height());

    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    leaderBoard = new LeaderBoard;

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->actionLvl_1->setDisabled(true);
    ui->actionLvl_2->setDisabled(true);
    ui->actionLvl_3->setDisabled(true);
    ui->actionLvl_4->setDisabled(true);
    ui->actionLvl_5->setDisabled(true);
    ui->actionRestart->setDisabled(true);
    ui->actionSave->setDisabled(true);
    ui->actionLoad->setDisabled(true);
    ui->actionSave_2->setDisabled(true);
}

MainWindow::~MainWindow()
{
    if(isSokobanStarted){
        delete lvl;
        delete view;
    }
    delete leaderBoard;
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(isSokobanStarted) {
        switch(event->key()) {
        case Qt::Key_W:
            lvl->MoveUp();
            view->PaintField(lvl);
            if(lvl->CheckWin()) {
                QWidget* win = new winWidget();
                win->show();
                isSokobanStarted = false;
            }
            break;
        case Qt::Key_S:
            lvl->MoveDown();
            view->PaintField(lvl);
            if(lvl->CheckWin()) {
                QWidget* win = new winWidget();
                win->show();
                isSokobanStarted = false;
            }
            break;

        case Qt::Key_A:
            lvl->MoveLeft();
            view->PaintField(lvl);
            if(lvl->CheckWin()) {
                QWidget* win = new winWidget();
                win->show();
                isSokobanStarted = false;
            }
            break;

        case Qt::Key_D:
            lvl->MoveRight();
            view->PaintField(lvl);
            if(lvl->CheckWin()) {
                QWidget* win = new winWidget();
                win->show();
                isSokobanStarted = false;
            }
            break;
        }
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    ui->graphicsView->setFixedHeight(ui->centralwidget->height());
    ui->graphicsView->setFixedWidth(ui->centralwidget->width());
    ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::on_actionNew_game_triggered()
{
    if(isSokobanStarted) {
        delete lvl;
        delete view;
    }
    isSokobanStarted = true;
    ui->actionSave_2->setEnabled(true);
    ui->actionRestart->setEnabled(true);
    ui->actionSave->setEnabled(true);
    ui->actionLvl_1->setEnabled(true);
    ui->actionLvl_2->setEnabled(true);
    ui->actionLvl_3->setEnabled(true);
    ui->actionLvl_4->setEnabled(true);
    ui->actionLvl_5->setEnabled(true);
    lvl = new Level("1");
    lvl->InitializeUserData();
    view = new View(scene);

    view->PaintField(lvl);
    ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::on_actionRestart_triggered()
{
    lvl->restart();
    view->PaintField(lvl);

}


void MainWindow::on_actionSave_triggered()
{
    ui->actionLoad->setEnabled(true);
    lvl->saveGame();
}

void MainWindow::on_actionSave_2_triggered()
{
    QString userName = QInputDialog::getText(this, "", "Enter USENAME");
    lvl->saveUserData(userName);
}


void MainWindow::on_actionLoad_2_triggered()
{
    delete leaderBoard;
    leaderBoard = new LeaderBoard;
    leaderBoard->show();
}


void MainWindow::on_actionLvl_1_triggered()
{
    lvl->loadLevel("1");
    view->PaintField(lvl);
    isSokobanStarted = true;
}


void MainWindow::on_actionLvl_2_triggered()
{
    lvl->loadLevel("2");
    view->PaintField(lvl);
    isSokobanStarted = true;
}


void MainWindow::on_actionLvl_3_triggered()
{
    lvl->loadLevel("3");
    view->PaintField(lvl);
    isSokobanStarted = true;
}


void MainWindow::on_actionLvl_4_triggered()
{
    lvl->loadLevel("4");
    view->PaintField(lvl);
    isSokobanStarted = true;
}


void MainWindow::on_actionLvl_5_triggered()
{
    lvl->loadLevel("5");
    view->PaintField(lvl);
    isSokobanStarted = true;
}


void MainWindow::on_actionLoad_triggered()
{
    lvl->loadSave("user_save");
    view->PaintField(lvl);
    isSokobanStarted = true;
}

