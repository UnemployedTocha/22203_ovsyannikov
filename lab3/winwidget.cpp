#include "winwidget.h"
#include "ui_winwidget.h"

winWidget::winWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::winWidget)
{
    ui->setupUi(this);
}

winWidget::~winWidget()
{
    delete ui;
}

void winWidget::on_pushButton_clicked()
{
    this->close();
}

