#include "view.h"

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QFile>

View::View(QGraphicsScene* scene)
{
    scene_ = scene;
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
    scene_->clear();
    QString path = "C:/Users/Pepega/Documents/Qt/PeepoSad3/Saves/leaderboard_save";
    QFile leaderboardFile(path);

    if (leaderboardFile.open(QIODevice::ReadOnly | QIODevice::Text)) {

    }


    leaderboardFile.close();
}

void View::ProcessLine(const QString &line)
{

}

