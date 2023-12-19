#include "widget.h"

#include <QApplication>

#include <QString>
#include <QFile>
#include <iostream>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
