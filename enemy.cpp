#include "enemy.h"

Enemy* EnemyFactory::getEnemy(QString name, int x, int y)
{
    if(name == "soldier"){
        return new Soldier(x,y);
    }
    else if(name == "dog"){
        return new Dog(x, y);
    }
    else if(name == "plane"){
        return new Plane(x, y);
    }
    else if(name == "hammer"){
        return new Hammer(x, y);
    }
    else return new Bully(x, y);
}

Enemy::Enemy(QString name, int x, int y, int atk, int def, int hp, int s): Unit(x, y, atk, def, hp, name), speed(s){
    QTimer* timer = new QTimer;
    timer->start(33);
    connect(timer, SIGNAL(timeout()), this, SLOT(advance()));
}

bool Enemy::win()
{
    if((y < 200 && x < 200) || (y < 300 && x < 180) || (y < 400 && x < 160) || (y < 500 && x < 140)) return true;
    return false;
}

void Enemy::advance(){
    time_cnt = (time_cnt + 1) % 15;
    bool collide_with_executor = false;
    QList<QGraphicsItem *> colliding_items = collidingItems();

    for(auto ele: colliding_items){
        Executor* executor = dynamic_cast<Executor*>(ele);
        if (executor){
            if(std::abs(executor->gety() - y) > 30) continue;
            collide_with_executor = true;
            if(!battle && executor->passable()) continue;
            if(!battle) {
                battle = true;
//                executor->modifyHolding(1);
            }
            if(!time_cnt) executor->modifyHp(-atk);
        }
    }
    if(!collide_with_executor){
        imageNo = 0;
        battle = false;
    }
    if(battle && !time_cnt){
        imageNo = 1 - imageNo;
        update();
    }
    if(!battle){
        x -= speed;
        setPos(x, y);
    }
}


void Plane::advance()
{
    time_cnt = (time_cnt + 1) % 15;
    x -= speed;
    setPos(x, y);
}
