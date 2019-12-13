#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "unit.h"
#include "enemy.h"

class Enemy;

class Executor: public Unit{
public:
    Executor(QString name, int x, int y, int atk, int def, int hp, int r): Unit(x, y, atk, def, hp, name), resistance(r){}
    bool passable();
    bool injured();
    virtual void action(std::vector<Executor*> executors, std::vector<Enemy*> enemies);

private:
    int resistance;
};

class ExecutorFactory{
public:
    static Executor* getExecutor(QString name, int x, int y);
};


class Texas: public Executor{
public:
    Texas(int x,int y): generateCost(375), Executor("texas", x, y, 510, 250, 1400, 2){}
    void action(std::vector<Executor*> executors, std::vector<Enemy*> enemies);
    int generateCost;
};

class Bluepoison: public Executor{
public:
    Bluepoison(int x,int y): Executor("bluepoison", x, y, 590, 100, 1000, 1){}
    void action(std::vector<Executor*> executors, std::vector<Enemy*> enemies);

};

class Gugu: public Executor{
public:
    Gugu(int x,int y): Executor("gugu", x, y, 300, 150, 1200, 1){}
    void action(std::vector<Executor*> executors, std::vector<Enemy*> enemies);
};

class Silverash: public Executor{
public:
    Silverash(int x,int y): Executor("silverash", x, y, 750, 400, 2200, 2){}

};

class Saria: public Executor{
public:
    Saria(int x,int y): Executor("saria", x, y, 400, 600, 3000, 3){}

};

class Specter: public Executor{
public:
    Specter(int x,int y): Executor("specter", x, y, 500, 300, 2000, 3){}
    void action(std::vector<Executor*> executors, std::vector<Enemy*> enemies);
};

#endif // EXECUTOR_H
