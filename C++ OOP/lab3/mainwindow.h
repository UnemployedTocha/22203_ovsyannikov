#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "view.h"
#include "level.h"
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Sokoban : public QMainWindow
{
    Q_OBJECT

public:
    Sokoban(QMainWindow* parent = nullptr);
    ~Sokoban();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    View* view;
    Level* lvl;
    QPixmap menuPic;
    QPixmap winPic;

    bool isSokobanStarted = false;
    void LevelTrigger(const QString& lvlName);
protected:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
private slots:
    void on_actionNew_game_triggered();
    void on_actionRestart_triggered();
    void on_actionSave_triggered();
    void on_actionLoad_triggered();
    void on_actionSave_2_triggered();
    void on_actionLoad_2_triggered();
    void on_actionLvl_1_triggered();
    void on_actionLvl_2_triggered();
    void on_actionLvl_3_triggered();
    void on_actionLvl_4_triggered();
    void on_actionLvl_5_triggered();
};
#endif // MAINWINDOW_H
