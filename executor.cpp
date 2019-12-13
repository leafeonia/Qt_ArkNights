#include "executor.h"

Executor* ExecutorFactory::getExecutor(QString name, int x, int y)
{
    if (name == "texas"){
        return new Texas(x, y);
    }
    else if(name == "bluepoison"){
        return new Bluepoison(x, y);
    }
    else if(name == "gugu"){
        return new Gugu(x, y);
    }
    else if(name == "silverash"){
        return new Silverash(x, y);
    }
    else if(name == "saria"){
        return new Saria(x, y);
    }
    else
        return new Specter(x, y);
}


bool Executor::passable()
{
    QList<QGraphicsItem*> collide = collidingItems();
    int cnt = 0;
    for(int i = 0;i < collide.size();i++){
        Enemy* enemy = dynamic_cast<Enemy*>(collide[i]);
        if(!enemy || typeid(enemy) == typeid(Plane)) continue;
        else if(std::abs(enemy->gety() - y) < 50) {
            if(typeid(*enemy) == typeid(Bully)) cnt += 3;
            else cnt++;
        }
    }
    return cnt > resistance; //不能用等于，因为此时新来的enemy也是collidingItem，如果等于就漏了
}

bool Executor::injured()
{
    return hp < maxhp;
}

void Executor::action(std::vector<Executor*> executors, std::vector<Enemy *> enemies)
{
    time_cnt = (time_cnt + 1) % 15;
    bool collide_with_enemy = false;
    QList<QGraphicsItem *> colliding_items = collidingItems();

    for(auto ele: colliding_items){
        Enemy* enemy = dynamic_cast<Enemy*>(ele);
        if (enemy && typeid(*enemy) != typeid(Plane)){
            if(std::abs(enemy->gety() - y) > 30) continue;
            collide_with_enemy = true;
            if(!battle) battle = true;
            if(!time_cnt) {
                enemy->modifyHp(-atk);
//                if(enemy->getHp() <= 0) modifyHolding(-1);
            }
            break;
        }
    }
    if(!collide_with_enemy){
        imageNo = 0;
        battle = false;
    }
    if(battle && !time_cnt){
        imageNo = 1 - imageNo;
    }
    update();
}

void Bluepoison::action(std::vector<Executor*> executors, std::vector<Enemy *> enemies)
{
    time_cnt = (time_cnt + 1) % 10;
    Enemy* target = NULL;
    for(auto enemy: enemies){
        if(abs(enemy->gety() - y) < 150 && 0 < enemy->getx() - x && enemy->getx() - x < 400){
            if(!battle) battle = true;
            if(!target) target = enemy;
            else{
                if(typeid(*target) == typeid(Plane)){
                    if(typeid(*enemy) == typeid(Plane) && enemy->getx() < target->getx()) target = enemy;
                }
                else if(enemy->getx() < target->getx()) target = enemy;
            }
        }
    }
    if(!time_cnt && target) {
        target->modifyHp(-atk);
    }
    if(!target){
        imageNo = 0;
        battle = false;
    }
    if(battle && !time_cnt){
        imageNo = 1 - imageNo;
    }
    update();
}

void Gugu::action(std::vector<Executor*> executors, std::vector<Enemy *> enemies)
{
    time_cnt = (time_cnt + 1) % 25;
    bool team_injured = false;
    int gugu_x = 0, gugu_y = 0;
    for(int i = 0;i < executors.size();i++){
        if(executors[i] == this){
            gugu_x = i % 9;
            gugu_y = i / 9;
        }
    }
    for(int i = 0;i < executors.size();i++){
        if(executors[i] && executors[i]->injured()){
            int x_block = i % 9;
            int y_block = i / 9;
            if(-1 <= x_block - gugu_x && x_block - gugu_x <= 2 && std::abs(y_block - gugu_y) <= 1){
                team_injured = true;
                if(!battle) battle = true;
                if(!time_cnt) {
                    executors[i]->modifyHp(atk);
                }

            }
        }
    }
    if(!team_injured && !time_cnt){
        imageNo = 0;
        battle = false;
    }
    if(battle && !time_cnt){
        imageNo = 1 - imageNo;
    }
    update();
}

void Specter::action(std::vector<Executor *> executors, std::vector<Enemy *> enemies)
{
    time_cnt = (time_cnt + 1) % 15;
    bool collide_with_enemy = false;
    QList<QGraphicsItem *> colliding_items = collidingItems();

    for(auto ele: colliding_items){
        Enemy* enemy = dynamic_cast<Enemy*>(ele);
        if (enemy && typeid(*enemy) != typeid(Plane)){
            if(std::abs(enemy->gety() - y) > 30) continue;
            collide_with_enemy = true;
            if(!battle) battle = true;
            if(!time_cnt) {
                enemy->modifyHp(-atk);
            }
        }
    }
    if(!collide_with_enemy){
        imageNo = 0;
        battle = false;
    }
    if(battle && !time_cnt){
        imageNo = 1 - imageNo;
    }
    update();
}

void Texas::action(std::vector<Executor *> executors, std::vector<Enemy *> enemies)
{
    this->Executor::action(executors, enemies);
    generateCost = (generateCost + 1) % 600;
}
