#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Sokoban sokoban;
    sokoban.show();
    return a.exec();
}
