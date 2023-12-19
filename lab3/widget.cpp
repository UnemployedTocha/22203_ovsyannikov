#include "widget.h"
#include "./ui_widget.h"

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QKeyEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);


    lvl = new Level(1);
    view = new View(scene);
    view->PaintField(lvl);

}

Widget::~Widget()
{
    delete lvl;
    delete view;
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
    case Qt::Key_W:
        lvl->MoveUp();
        view->PaintField(lvl);
        break;
    case Qt::Key_S:
        lvl->MoveDown();
        view->PaintField(lvl);
        break;

    case Qt::Key_A:
        lvl->MoveLeft();
        view->PaintField(lvl);
        break;

    case Qt::Key_D:
        lvl->MoveRight();
        view->PaintField(lvl);
        break;
    }
}

