#include "Game.h"
#include <QBrush>
#include "executor.h"
#include "board.h"
#include <QDebug>
#include "block.h"

Game::Game(QWidget *parent)
{
    quota_val = 12;
    cost_val = 12;
    defeated_val = 0;
    defend_val = 5;

    cost_mp["saria"] = 21;
    cost_mp["silverash"] = 19;
    cost_mp["gugu"] = 17;
    cost_mp["bluepoison"] = 12;
    cost_mp["texas"] = 12;
    cost_mp["specter"] = 23;

    setMouseTracking(true);
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 1414, 695);
    setBackgroundBrush(QBrush(QImage(":/resource/bg.jpg")));

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1414, 695);

    coordinate = new Coordinate();

    block = new Block(10000,10000);
    scene->addItem(block);


    // set timer for addcost, generate new enemy
    mytimer = new Timer(this);
    QTimer * timer1 = new QTimer();
    QObject::connect(timer1,SIGNAL(timeout()),mytimer,SLOT(addCost()));
    timer1->start(500);

    QTimer* timer2 = new QTimer();
    QObject::connect(timer2,SIGNAL(timeout()),mytimer,SLOT(generateEnemy()));
    timer2->start(500);

    QTimer* centralClock = new QTimer();
    centralClock->start(33);
    QObject::connect(centralClock,SIGNAL(timeout()), mytimer, SLOT(executorBattle()));

    executors = std::vector<Executor*>(36, NULL);

    QGraphicsPixmapItem *scoreboard = new QGraphicsPixmapItem();
    scoreboard->setPixmap(QPixmap(":/resource/score.jpg"));
    scoreboard->setPos(500,0);
    scene->addItem(scoreboard);

    QGraphicsPixmapItem *costboard = new QGraphicsPixmapItem();
    costboard->setPixmap(QPixmap(":/resource/cost.jpg"));
    costboard->setPos(1250,445);
    scene->addItem(costboard);

    defeated = new QGraphicsTextItem();
    defeated->setPlainText("0");
    defeated->setDefaultTextColor(Qt::white);
    defeated->setFont(QFont("times",16));
    defeated->setPos(625,5);
    scene->addItem(defeated);

    defend = new QGraphicsTextItem();
    defend->setPlainText("5");
    defend->setDefaultTextColor(Qt::red);
    defend->setFont(QFont("times",16));
    defend->setPos(840,5);
    scene->addItem(defend);

    shop = new Shop(1414, 695, scene);
    show();
}

void Game::mousePressEvent(QMouseEvent *event)
{

    auto pos = coordinate->getCoordinate(event->x(), event->y());
    if(pos.first == -1 || shop->selected() == "" || executors[pos.first] || quota_val == 0 || cost_val < cost_mp[shop->selected()]) {
        QGraphicsView::mousePressEvent(event);
        return;
    }

    cost_val -= cost_mp[shop->selected()];
    shop->cost->setPlainText(QString::number(cost_val));
    Executor *executor = ExecutorFactory::getExecutor(shop->selected(), pos.second.first,pos.second.second - 20);
//    connect(centralClock, SIGNAL(timeout()), executor, SLOT(advance()));
    executors[pos.first] = executor;
    scene->addItem(executor);
    shop->clear();
    quota_val--;
    shop->quota->setPlainText(QString::number(quota_val));
    update();
}

void Game::mouseMoveEvent(QMouseEvent *event){
    auto pos = coordinate->getCoordinate(event->x(), event->y());
    if(pos.first == -1 || shop->selected() == "") {
        block->setPos(10000, 10000);
        return;
    }
    block->setPos(pos.second.first,pos.second.second);
}

void Game::mouseDoubleClickEvent(QMouseEvent *event){
    auto pos = coordinate->getCoordinate(event->x(), event->y());
    if(pos.first == -1 || !executors[pos.first]) {
        QGraphicsView::mousePressEvent(event);
        return;
    }
    scene->removeItem(executors[pos.first]);
    quota_val++;
    shop->quota->setPlainText(QString::number(quota_val));
    if(typeid(*executors[pos.first]) == typeid(Texas)){
        cost_val = std::min(cost_val+6, 99);
        shop->cost->setPlainText(QString::number(cost_val));
    }
    executors[pos.first] = NULL;
}

void Game::finish()
{
    QMessageBox box;
    box.setText("Score: " + QString::number(defeated_val));
    box.exec();
    exit(0);
}


