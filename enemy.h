#ifndef ENEMY_H
#define ENEMY_H

#include "unit.h"
#include "executor.h"

class EnemyFactory;

class Enemy: public Unit
{
public:
    Enemy(QString name, int x, int y, int atk, int def, int hp, int s);
    bool win();

public slots:
    virtual void advance();

protected:
    int speed;
};

class EnemyFactory{
public:
    static Enemy* getEnemy(QString name, int x, int y);
};

class Soldier: public Enemy{
public:
    Soldier(int x,int y): Enemy("soldier", x, y, 300, 400, 1000, 5){}

};

class Plane: public Enemy{
public:
    Plane(int x, int y): Enemy("plane", x, y, 0, 100, 1200, 5){}

public slots:
    void advance();
};

class Hammer: public Enemy{
public:
    Hammer(int x, int y): Enemy("hammer", x, y, 700, 400, 5000, 5){}
};

class Dog: public Enemy{
public:
    Dog(int x, int y): Enemy("dog", x, y, 200, 200, 1000, 10){}
};

class Bully: public Enemy{
public:
    Bully(int x, int y): Enemy("bully", x, y, 500, 400, 5000, 5){}
};

#endif // ENEMY_H
