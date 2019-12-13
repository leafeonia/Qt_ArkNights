#include "board.h"
#include <QDebug>

Board::Board(QString name, int x,int y, QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    this->x = x;
    this->y = y;
    this->name = name;
    selected = false;
    QString dir = ":/resource/"+name+".jpg";
    setPos(x, y);
    setPixmap(QPixmap(dir));
}



void Board::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        selected = 1 - selected;
    }
    updatePos();
}

void Board::updatePos()
{
    if(selected){
        setPos(x, y - 25);
    }
    else setPos(x, y);
}

