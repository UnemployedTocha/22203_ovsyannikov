#ifndef VIEW_H
#define VIEW_H

#include "fieldtype.h"
#include <QGraphicsScene>
#include <QTableWidget>
#include <QGraphicsView>
#include <vector>

class View
{
public:
    View(QGraphicsView* graphicsView, QGraphicsScene* scene, QTableWidget* leaderBoard);
    void PaintField(const std::vector<std::vector<FieldType>>& lvlField, unsigned stepsNumb);
    void PaintLeaderBoard();
private:
    struct UserData {
        QString lvlPassed;
        QString stepsTaken;
        QString userName;
    };

    QGraphicsView* graphicsView_;
    QGraphicsScene* scene_;
    QTableWidget* leaderBoard_;

    static bool Compare(const UserData& a, const UserData& b);
};

#endif // VIEW_H
