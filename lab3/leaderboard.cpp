#include "leaderboard.h"
#include "ui_leaderboard.h"


LeaderBoard::LeaderBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LeaderBoard)
{
    ui->setupUi(this);

    path = "C:/Users/Pepega/Documents/Qt/PeepoSad3/Saves/leaderboard_save.txt";
    QFile leaderboardFile(path);

    if (leaderboardFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        while (!leaderboardFile.atEnd()) {
            QString line = leaderboardFile.readLine();
            ProcessLine(line);
        }
    }

    leaderboardFile.close();
}

void LeaderBoard::Update()
{
    ui->tableWidget->clear();
    QFile leaderboardFile(path);

    if (leaderboardFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        while (!leaderboardFile.atEnd()) {
            QString line = leaderboardFile.readLine();
            ProcessLine(line);
        }
    }

    leaderboardFile.close();
}

LeaderBoard::~LeaderBoard()
{
    delete ui;
}


void LeaderBoard::ProcessLine(const QString& line)
{
    QStringList ss = line.split(' ');

    if(ui->tableWidget->rowCount() < row + 1) {
        ui->tableWidget->setRowCount(row + 1);
    }
    ui->tableWidget->setColumnCount(column);

    for(size_t column = 0; column < ss.size(); column++) {
        QTableWidgetItem* newItem = new QTableWidgetItem(ss.at(column));
        switch(row) {
        case 0:
            newItem->setBackground(Qt::yellow);
            break;
        case 1:
            newItem->setBackground(Qt::lightGray);
            break;
        case 2:
            newItem->setBackground(Qt::darkRed);
            break;
        }
            ui->tableWidget->setItem(row, column, newItem);
    }

    row++;
}
