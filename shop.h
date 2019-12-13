#ifndef SHOP_H
#define SHOP_H

#include "board.h"
#include <QDebug>
#include <QGraphicsScene>
#include <vector>
#include <QGraphicsTextItem>
#include <map>

class Shop{
public:
    Shop(int corner_x, int corner_y, QGraphicsScene* scene);
    QString selected();
    void clear();
    friend class Game;
    friend class Timer;
private:
    std::vector<Board*> boards;
    QGraphicsTextItem* quota, *cost; //剩余部署人数，部署费用
};

#endif // SHOP_H
