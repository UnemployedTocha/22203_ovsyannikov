#ifndef VIEW_H
#define VIEW_H

#include "level.h"
#include <QGraphicsScene>

class View
{
public:
    View(QGraphicsScene* scene);
    void PaintField(Level* lvl);

private:
    QRectF GetRectItem();
    QGraphicsScene* scene_;
};

#endif // VIEW_H
