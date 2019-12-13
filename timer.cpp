#include "timer.h"

Timer::Timer(Game *game, QObject *parent): QObject(parent)
{
    this->game = game;
    difficulty_timer = 0;
    difficulty = 100;
    srand(time(NULL));
}

void Timer::addCost()
{
    if(game->cost_val < 99) game->cost_val += 1;
    game->shop->cost->setPlainText(QString::number(game->cost_val));
    game->update();
}

void Timer::generateEnemy()
{
    difficulty_timer++;
    if(difficulty > 20) difficulty--;
    int random = rand() % difficulty;
    QString name = "";
    if(random < 3) name = "soldier";
    else if(random < 6) name = "dog";
    else if(random < 8 && difficulty_timer > 15) name = "plane";
    else if(random == 9 && difficulty_timer > 60) name = "hammer";
    else if(random == 10 && difficulty_timer > 90) name = "bully";
    if(name == "") return;
    int row = rand() % 4;
    Enemy* enemy = EnemyFactory::getEnemy(name, 1300, 100 + 100 * row);
    game->enemys.push_back(enemy);
    game->scene->addItem(enemy);
    game->update();
}

void Timer::executorBattle()
{
    for(int i = 0;i < game->executors.size();i++){
        if(game->executors[i]){
            game->executors[i]->action(game->executors, game->enemys);
            if(typeid(*(game->executors[i])) == typeid(Texas)){
                Texas* texas = dynamic_cast<Texas*>(game->executors[i]);
                if(texas && texas->generateCost == 0){
                    game->cost_val = std::min(99, game->cost_val + 12);
                    game->shop->cost->setPlainText(QString::number(game->cost_val));
                }
            }
        }
    }

    for(int i = 0;i < game->executors.size();i++){
        if(game->executors[i] && game->executors[i]->getHp() <= 0){
            game->quota_val++;
            game->shop->quota->setPlainText(QString::number(game->quota_val));
            Executor* dead = game->executors[i];
            game->executors[i] = NULL;
            game->scene->removeItem(dead);
        }
    }

    int idx = 0;
    while(idx < game->enemys.size()){
        if(game->enemys[idx]->getHp() <= 0 || game->enemys[idx]->win()){
            if(game->enemys[idx]->win()) {
                game->defend_val--;
                game->defend->setPlainText(QString::number(game->defend_val));
                if(game->defend_val <= 0) game->finish();
            }
            else{
                game->defeated_val++;
                game->defeated->setPlainText(QString::number(game->defeated_val));
            }
            Enemy* dead = game->enemys[idx];
            game->enemys.erase(game->enemys.begin() + idx);
            game->scene->removeItem(dead);
//            delete dead;
            continue;
        }
        else idx++;
    }
}


