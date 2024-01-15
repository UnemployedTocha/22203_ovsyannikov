#ifndef VIEW_H
#define VIEW_H

#include "level.h"
#include <QGraphicsScene>

class View
{
public:
    View(QGraphicsScene* scene);
    void PaintField(Level* lvl);
    void PaintLeaderBoard();
private:
    QGraphicsScene* scene_;
    void ProcessLine(const QString& line);
};

#endif // VIEW_H
