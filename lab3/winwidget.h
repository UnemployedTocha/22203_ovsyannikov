#ifndef WINWIDGET_H
#define WINWIDGET_H

#include <QWidget>

namespace Ui {
class winWidget;
}

class winWidget : public QWidget
{
    Q_OBJECT

public:
    explicit winWidget(QWidget *parent = nullptr);
    ~winWidget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::winWidget *ui;
};

#endif // WINWIDGET_H
