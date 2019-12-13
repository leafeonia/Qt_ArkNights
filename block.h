#ifndef BLOCK_H
#define BLOCK_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>


class Block: public QGraphicsPixmapItem{
public:
    Block(int x, int y, QGraphicsItem * parent=0);

private:
    int x, y;
};

#endif // BLOCK_H
