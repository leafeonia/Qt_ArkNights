#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <Qstring>

class Board: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Board(QString name, int x,int y, QGraphicsItem* parent = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void updatePos();
    friend class Shop;
private:
    int x, y;
    QString name;
    bool selected;
};

#endif // BOARD_H
