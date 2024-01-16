#ifndef VIEW_H
#define VIEW_H

#include "level.h"
#include <QGraphicsScene>
#include <QTableWidget>

class View
{
public:
    View(QGraphicsScene* scene, QTableWidget* leaderBoard);
    void PaintField(Level* lvl);
    void PaintLeaderBoard();
private:
    QGraphicsScene* scene_;
    QTableWidget* leaderBoard_;

    void ProcessLine(const QString& line);
};

#endif // VIEW_H
