#include "block.h"
#include <QDebug>

Block::Block(int x, int y, QGraphicsItem * parent): QGraphicsPixmapItem(parent), x(x), y(y)
{
    setPos(x, y);
    setPixmap(QPixmap(":/resource/mask.png"));
    setOpacity(0.5);
}
