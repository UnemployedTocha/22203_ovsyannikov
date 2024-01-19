#include "view.h"

#include <QGraphicsView>
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

void View::PaintField(Level* lvl)
{
    scene_->clear();
    size_t lineObjCounter = 0;

    for (size_t i = 0; i < lvl->GetLineNumb(); i++) {
        lineObjCounter = 0;
        QPen pen(Qt::NoPen);
        for (auto it = lvl->Begin(i); it != lvl->End(i); ++it) {    
            QBrush brush("azure");
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
            data.userName = in.read(50);
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

