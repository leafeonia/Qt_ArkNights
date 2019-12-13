#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include "game.h"
#include "enemy.h"
#include <stdlib.h>
#include <time.h>

class Game;

class Timer : public QObject
{
    Q_OBJECT
public:
    explicit Timer(Game* game, QObject *parent = nullptr);

signals:

public slots:
    void addCost();
    void generateEnemy();
    void executorBattle();

private:
    Game* game;
    int difficulty_timer, difficulty;
};

#endif // TIMER_H
