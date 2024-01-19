#ifndef VIEW_H
#define VIEW_H

#include "level.h"
#include <QGraphicsScene>
#include <QTableWidget>
#include <QGraphicsView>
class View
{
public:
    View(QGraphicsView* graphicsView, QGraphicsScene* scene, QTableWidget* leaderBoard);
    void PaintField(Level* lvl);
    void PaintLeaderBoard();
private:
    struct UserData {
        QString lvlPassed;
        QString stepsTaken;
        QString userName;
    };

    bool isleaderBoardPainted = false;
    QGraphicsView* graphicsView_;
    QGraphicsScene* scene_;
    QTableWidget* leaderBoard_;

    static bool Compare(const UserData& a, const UserData& b);
};

#endif // VIEW_H
