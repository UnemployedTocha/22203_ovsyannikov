#include "view.h"

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QFile>

View::View(QGraphicsScene* scene, QTableWidget* leaderBoard)
{
    scene_ = scene;
    leaderBoard_ = leaderBoard;
}

void View::PaintField(Level* lvl)
{
    scene_->clear();
    size_t lineObjCounter = 0;

    for (size_t i = 0; i < lvl->GetLineNumb(); i++) {
        lineObjCounter = 0;
        for (auto it = lvl->Begin(i); it != lvl->End(i); ++it) {


            QBrush brush("azure");
            QPen pen(Qt::NoPen);
            switch(*it) {
            case FieldType::PLAYER :
                brush.setColor("darkred");
                break;
            case FieldType::BOX:
                brush.setColor("chocolate");
                break;
            case FieldType::WALL:
                brush.setColor("black");
                brush.setStyle(Qt::Dense5Pattern);
                break;
            case FieldType::GOAL:
                brush.setColor("gold");
                break;
            case FieldType::BOX_ON_GOAL:
                brush.setStyle(Qt::Dense1Pattern);
                brush.setColor("chocolate");
                break;
            case FieldType::PLAYER_ON_GOAL:
                brush.setStyle(Qt::Dense1Pattern);
                brush.setColor("darkred");
                break;
            }


            QRect rectItem(lineObjCounter * 30, i * 30, 30, 30);
            scene_->addRect(rectItem,  pen, brush);
            ++lineObjCounter;
        }
    }
    QGraphicsTextItem * stepsNum = new QGraphicsTextItem;
    QGraphicsTextItem * text = new QGraphicsTextItem;
    stepsNum->setPlainText(QString::number(lvl->GetStepsCounter()));
    text->setPlainText("Steps: ");
    text->setPos(0, lvl->GetLineNumb() * 30);
    stepsNum->setPos(35, lvl->GetLineNumb() * 30);
    scene_->addItem(text);
    scene_->addItem(stepsNum);

}

void View::PaintLeaderBoard() {
    QString path = "C:/Users/Pepega/Documents/Qt/PeepoSad3/Saves/leaderboard_save.txt";
    QFile leaderboardFile(path);

    if (leaderboardFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        while (!leaderboardFile.atEnd()) {
            QString line = leaderboardFile.readLine();
            ProcessLine(line);
        }
    }

    leaderboardFile.close();
}

void View::ProcessLine(const QString &line)
{
    QStringList ss = line.split(' ');

//    if(ui->tableWidget->rowCount() < 10) {
    leaderBoard_->setRowCount(10);
//    }
    leaderBoard_->setColumnCount(3);

    int row = 0;
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
        leaderBoard_->setItem(row, column, newItem);
    }

    row++;
}

