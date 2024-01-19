#include "view.h"

#include <QGraphicsItem>
#include <QFile>
#include <QDirIterator>
#include <algorithm>

View::View(QGraphicsView* graphicsView,QGraphicsScene* scene, QTableWidget* leaderBoard)
{
    graphicsView_ = graphicsView;
    scene_ = scene;
    leaderBoard_ = leaderBoard;
}

void View::PaintField(const std::vector<std::vector<FieldType>>& lvlField, unsigned stepsNumb)
{
    scene_->clear();
    size_t columnObjCounter = 0;

    for (auto it1 = lvlField.begin(); it1 != lvlField.end(); ++it1) {
        size_t lineObjCounter = 0;
        QPen pen(Qt::NoPen);
        for (auto it2 = (*it1).begin(); it2 != (*it1).end(); ++it2) {

            QBrush brush("azure");
            switch(*it2) {
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

            QRect rectItem(lineObjCounter * 30, columnObjCounter * 30, 30, 30);
            scene_->addRect(rectItem,  pen, brush);
            ++lineObjCounter;
        }
        ++columnObjCounter;
    }
    QGraphicsTextItem * stepsNum = new QGraphicsTextItem;
    QGraphicsTextItem * text = new QGraphicsTextItem;
    stepsNum->setPlainText(QString::number(stepsNumb));
    text->setPlainText("Steps: ");
    text->setPos(0, columnObjCounter * 30);
    stepsNum->setPos(35, columnObjCounter * 30);
    scene_->addItem(text);
    scene_->addItem(stepsNum);

    scene_->setSceneRect(scene_->itemsBoundingRect());
    graphicsView_->fitInView(scene_->sceneRect(), Qt::KeepAspectRatio);
}

bool View::Compare(const UserData& a, const UserData& b)
{
    if(a.lvlPassed.toInt() > b.lvlPassed.toInt()) {
        return true;
    }
    else if(a.lvlPassed.toInt() < b.lvlPassed.toInt()) {
        return false;
    }
    else {
        return (a.stepsTaken.toInt() >= b.stepsTaken.toInt()) ? false : true;
    }
}

void View::PaintLeaderBoard() {
    leaderBoard_->clear();
    QString path = "C:/Users/Pepega/Documents/Qt/PeepoSad3/LeaderboardSaves";

    QDir dir(path);
    dir.setFilter( QDir::Files | QDir::NoDotAndDotDot);
    if(dir.isEmpty()) {
        return;
    }

    QDirIterator it(dir);
    std::vector<UserData> userDataArr;
    do{
        QFile userData(it.next());
        if (userData.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&userData);
            UserData data;
            in >> data.lvlPassed;
            in >> data.stepsTaken;
            data.userName = in.readAll();
            userDataArr.push_back(data);
        }
        userData.close();
    }while(it.hasNext());

    std::sort(userDataArr.begin(), userDataArr.end(), Compare);

    static constexpr size_t columnNum = 3;
    leaderBoard_->setRowCount(userDataArr.size());
    leaderBoard_->setColumnCount(columnNum);
    QStringList labels;
    labels << "Levels passed" << "Steps taken" << "Username";
    leaderBoard_->setHorizontalHeaderLabels(labels);

    for(size_t row = 0; row < userDataArr.size(); ++row) {
        QTableWidgetItem* levels = new QTableWidgetItem(userDataArr[row].lvlPassed);
        QTableWidgetItem* steps = new QTableWidgetItem(userDataArr[row].stepsTaken);
        QTableWidgetItem* username = new QTableWidgetItem(userDataArr[row].userName);
        switch(row) {
        case 0:
            levels->setBackground(Qt::yellow);
            steps->setBackground(Qt::yellow);
            username->setBackground(Qt::yellow);
            break;
        case 1:
            levels->setBackground(Qt::lightGray);
            steps->setBackground(Qt::lightGray);
            username->setBackground(Qt::lightGray);
            break;
        case 2:
            levels->setBackground(Qt::darkRed);
            steps->setBackground(Qt::darkRed);
            username->setBackground(Qt::darkRed);
            break;
        }
        leaderBoard_->setItem(row, 0, levels);
        leaderBoard_->setItem(row, 1, steps);
        leaderBoard_->setItem(row, 2, username);
    }
}

