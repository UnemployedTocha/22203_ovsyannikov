#include "mainwindow.h"
#include "./ui_mainwindow.h"


#include <QGraphicsView>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QInputDialog>
#include <QString>

Sokoban::Sokoban(QMainWindow *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Sokoban");
    ui->stackedWidget->setFixedSize(ui->centralwidget->size());
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    ui->stackedWidget->setCurrentIndex(2);

    menuPic.load("C:/Users/Pepega/Documents/Qt/PeepoSad3/Images/Menu.png");
    ui->label_pic->setPixmap(menuPic);
    winPic.load("C:/Users/Pepega/Documents/Qt/PeepoSad3/Images/Win.png");
    ui->label_pic_2->setPixmap(winPic);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    ui->actionLvl_1->setDisabled(true);
    ui->actionLvl_2->setDisabled(true);
    ui->actionLvl_3->setDisabled(true);
    ui->actionLvl_4->setDisabled(true);
    ui->actionLvl_5->setDisabled(true);
    ui->actionRestart->setDisabled(true);
    ui->actionSave->setDisabled(true);
    ui->actionLoad->setDisabled(true);
    ui->actionSave_2->setDisabled(true);
    ui->actionLoad_2->setDisabled(true);

    setFocusPolicy(Qt::StrongFocus);
}

Sokoban::~Sokoban()
{
    if(isSokobanStarted){
        delete lvl;
        delete view;
    }
    delete scene;
    delete ui;
}

void Sokoban::keyPressEvent(QKeyEvent *event)
{
    if(isSokobanStarted) {
        switch(event->key()) {
        case Qt::Key_W:
            lvl->MoveUp();
            view->PaintField(lvl->GetGameField(), lvl->GetStepsCounter());
            if(lvl->CheckWin()) {
                ui->stackedWidget->setCurrentIndex(3);
            }
            break;
        case Qt::Key_S:
            lvl->MoveDown();
            view->PaintField(lvl->GetGameField(), lvl->GetStepsCounter());
            if(lvl->CheckWin()) {
                ui->stackedWidget->setCurrentIndex(3);
            }
            break;
        case Qt::Key_A:
            lvl->MoveLeft();
            view->PaintField(lvl->GetGameField(), lvl->GetStepsCounter());
            if(lvl->CheckWin()) {
                ui->stackedWidget->setCurrentIndex(3);
            }
            break;

        case Qt::Key_D:
            lvl->MoveRight();
            view->PaintField(lvl->GetGameField(), lvl->GetStepsCounter());
            if(lvl->CheckWin()) {
                ui->stackedWidget->setCurrentIndex(3);
            }
            break;
        }
    }
}

void Sokoban::resizeEvent(QResizeEvent *event)
{
    ui->stackedWidget->setFixedHeight(ui->centralwidget->height());
    ui->stackedWidget->setFixedWidth(ui->centralwidget->width());
    ui->graphicsView->resize(ui->centralwidget->size());
    ui->label_pic->resize(ui->centralwidget->size());
    ui->label_pic->setPixmap(menuPic.scaled(ui->label_pic->size(), Qt::IgnoreAspectRatio));
    ui->label_pic_2->resize(ui->centralwidget->size());
    ui->label_pic_2->setPixmap(winPic.scaled(ui->label_pic_2->size(), Qt::IgnoreAspectRatio));
    ui->tableWidget->resize(ui->centralwidget->size());

    ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

void Sokoban::on_actionNew_game_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
    if(!isSokobanStarted) {
        lvl = new Level("1");
        view = new View(ui->graphicsView, scene, ui->tableWidget);
    }
    isSokobanStarted = true;
    ui->actionLoad->setEnabled(false);
    ui->actionSave_2->setEnabled(true);
    ui->actionRestart->setEnabled(true);
    ui->actionSave->setEnabled(true);
    ui->actionLvl_1->setEnabled(true);
    ui->actionLvl_2->setEnabled(true);
    ui->actionLvl_3->setEnabled(true);
    ui->actionLvl_4->setEnabled(true);
    ui->actionLvl_5->setEnabled(true);
    ui->actionLoad_2->setEnabled(true);


    lvl->newGame();
    view->PaintField(lvl->GetGameField(), lvl->GetStepsCounter());
}

void Sokoban::on_actionRestart_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
    lvl->restart();
    view->PaintField(lvl->GetGameField(), lvl->GetStepsCounter());

}


void Sokoban::on_actionSave_triggered()
{
    ui->actionLoad->setEnabled(true);
    lvl->saveGame();
}

void Sokoban::on_actionSave_2_triggered()
{
    QString userName = QInputDialog::getText(this, "", "Enter USERNAME");
    std::string s = userName.toStdString();
    lvl->saveUserData(QString::fromStdString(s.substr(0, 20)));
}


void Sokoban::on_actionLoad_2_triggered()
{
    view->PaintLeaderBoard();
    ui->stackedWidget->setCurrentIndex(1);
}

void Sokoban::LevelTrigger(const QString& lvlName) {
    ui->stackedWidget->setCurrentIndex(0);
    lvl->loadLevel(lvlName);
    view->PaintField(lvl->GetGameField(), lvl->GetStepsCounter());
}

void Sokoban::on_actionLvl_1_triggered()
{
    LevelTrigger("1");
}

void Sokoban::on_actionLvl_2_triggered()
{
    LevelTrigger("2");
}

void Sokoban::on_actionLvl_3_triggered()
{
    LevelTrigger("3");
}

void Sokoban::on_actionLvl_4_triggered()
{
    LevelTrigger("4");
}

void Sokoban::on_actionLvl_5_triggered()
{
    LevelTrigger("5");
}


void Sokoban::on_actionLoad_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
    lvl->loadSave("user_save");
    view->PaintField(lvl->GetGameField(), lvl->GetStepsCounter());
}

