#include "shop.h"

Shop::Shop(int corner_x, int corner_y, QGraphicsScene* scene)
{
    QString names[] = {"specter","saria", "silverash", "gugu", "bluepoison", "texas"};
    for(auto name: names){
        Board* board = new Board(name, corner_x - 120, corner_y - 120);
        corner_x -= 120;
        scene->addItem(board);
        boards.push_back(board);
    }

    QGraphicsPixmapItem* quotaboard = new QGraphicsPixmapItem();
    quotaboard->setPos(1180, 510);
    quotaboard->setPixmap(QPixmap(":/resource/quota_text.jpg"));
    scene->addItem(quotaboard);

    quota = new QGraphicsTextItem();
    quota->setPlainText("12");
    quota->setDefaultTextColor(Qt::white);
    quota->setFont(QFont("times",15));
    quota->setPos(1375,512);
    scene->addItem(quota);

    cost = new QGraphicsTextItem();
    cost->setPlainText("12");
    cost->setDefaultTextColor(Qt::white);
    cost->setFont(QFont("times",35));
    cost->setPos(1330,450);
    scene->addItem(cost);

}


QString Shop::selected()
{
    for(auto ele: boards){
        if(ele->selected) return ele->name;
    }
    return "";
}

void Shop::clear()
{
    for(auto ele: boards) {
        ele->selected = false;
        ele->updatePos();
    }
}

