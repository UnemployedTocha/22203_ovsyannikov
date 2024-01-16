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

Sokoban::Sokoban(QMainWindow *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setFocusPolicy(Qt::StrongFocus);
    ui->setupUi(this);

    ui->stackedWidget->setFixedSize(ui->centralwidget->size());
//    ui->graphicsView->setSceneRect(0, 0, ui->stackedWidget->width(), ui->stackedWidget->height());
//    scene = new QGraphicsScene(0, 0, ui->graphicsView->width(), ui->graphicsView->height());
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
//    ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

    ui->stackedWidget->setCurrentIndex(0);
//    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
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

Sokoban::~Sokoban()
{
    if(isSokobanStarted){
        delete lvl;
        delete view;
    }
    delete leaderBoard;
    delete ui;
}

void Sokoban::keyPressEvent(QKeyEvent *event)
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

void Sokoban::resizeEvent(QResizeEvent *event)
{
    ui->stackedWidget->setFixedHeight(ui->centralwidget->height());
    ui->stackedWidget->setFixedWidth(ui->centralwidget->width());
    ui->graphicsView->setFixedHeight(ui->centralwidget->height());
    ui->graphicsView->setFixedWidth(ui->centralwidget->width());

    ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
//    scene->setSceneRect(0, 0, ui->stackedWidget->width(), ui->stackedWidget->height());
}

void Sokoban::on_actionNew_game_triggered()
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
    view = new View(scene, ui->tableWidget);

    view->PaintField(lvl);
    view->PaintLeaderBoard();

//    scene->setSceneRect(0, 0, ui->centralwidget->width(), ui->centralwidget->height());
//    ui->graphicsView->setSceneRect(0, 0, ui->centralwidget->width(), ui->centralwidget->height());
    ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

void Sokoban::on_actionRestart_triggered()
{
    lvl->restart();
    view->PaintField(lvl);

}


void Sokoban::on_actionSave_triggered()
{
    ui->actionLoad->setEnabled(true);
    lvl->saveGame();
}

void Sokoban::on_actionSave_2_triggered()
{
    QString userName = QInputDialog::getText(this, "", "Enter USENAME");
    lvl->saveUserData(userName);
}


void Sokoban::on_actionLoad_2_triggered()
{
//    delete leaderBoard;
//    leaderBoard = new LeaderBoard;
//    leaderBoard->show();
    ui->stackedWidget->setCurrentIndex(1);
}


void Sokoban::on_actionLvl_1_triggered()
{
    lvl->loadLevel("1");
    view->PaintField(lvl);
    isSokobanStarted = true;
}


void Sokoban::on_actionLvl_2_triggered()
{
    lvl->loadLevel("2");
    view->PaintField(lvl);
    isSokobanStarted = true;
}


void Sokoban::on_actionLvl_3_triggered()
{
    lvl->loadLevel("3");
    view->PaintField(lvl);
    ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    isSokobanStarted = true;
}


void Sokoban::on_actionLvl_4_triggered()
{
    lvl->loadLevel("4");
    view->PaintField(lvl);
    isSokobanStarted = true;
}


void Sokoban::on_actionLvl_5_triggered()
{
    lvl->loadLevel("5");
    view->PaintField(lvl);
    isSokobanStarted = true;
}


void Sokoban::on_actionLoad_triggered()
{
    lvl->loadSave("user_save");
    view->PaintField(lvl);
    isSokobanStarted = true;
}

