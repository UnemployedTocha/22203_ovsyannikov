#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include "view.h"
#include "level.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QGraphicsScene* scene;
    View* view;
    Level* lvl;

protected:
    virtual void keyPressEvent(QKeyEvent *event);
};
#endif // WIDGET_H
