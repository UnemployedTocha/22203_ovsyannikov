#include "view.h"

#include <QGraphicsView>
View::View(QGraphicsScene* scene)
{
    scene_ = scene;
}

//QRectF rectItem(lineObjCounter * 25, i * 25, 25, 25);
//scene_->addRect(rectItem,  QPen(), QBrush(Qt::cyan));

void View::PaintField(Level* lvl)
{
    scene_->clear();

    for (size_t i = 0; i < lvl->GetLineNumb(); i++) {
        size_t lineObjCounter = 0;
        for (auto it = lvl->Begin(i); it != lvl->End(i); ++it) {


            QBrush brush("azure");
            QPen pen("black");
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
}

