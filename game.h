#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QMouseEvent>
#include "block.h"
#include "coordinate.h"
#include "board.h"
#include "shop.h"
#include <vector>
#include "executor.h"
#include <QTimer>
#include <QObject>
#include "timer.h"
#include "unit.h"
#include "enemy.h"
#include <QMessageBox>

class Timer;

class Game: public QGraphicsView{
public:
    Game(QWidget* parent = 0);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void finish();
    QGraphicsScene *scene;
    friend class Timer;

private:
    Block* block;
    Coordinate* coordinate;
    Shop* shop;
    Timer* mytimer;
    std::vector<Executor*> executors;
    std::vector<Enemy*> enemys;
    QGraphicsTextItem *defeated, *defend;
    int quota_val, cost_val, defeated_val, defend_val;
    std::map<QString,int> cost_mp;
};


#endif // GAME_H
