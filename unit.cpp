#include "unit.h"

Unit::Unit(int x, int y, int atk, int def, int hp, QString name, QObject *parent): x(x), y(y), atk(atk), def(def), maxhp(hp), hp(hp), QObject(parent)
{
    setPos(x, y);
    image = QImage(":/resource/" + name + "_model.png");
    image_battle = QImage(":/resource/" + name + "_battle.png");
    imageNo = 0;
    battle = false;
    time_cnt = 0;
}

void Unit::modifyHp(int val)
{
    if(val < 0) hp += std::min(-10, val + def);
    else hp = std::min(maxhp, hp + val);
}

int Unit::getHp()
{
    return hp;
}

int Unit::getx()
{
    return x;
}

int Unit::gety()
{
    return y;
}

QRectF Unit::boundingRect() const
{
    return QRectF(0, 0, image.width(), image.height() + 5);
}

void Unit::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(imageNo == 1) painter->drawImage(QRectF(0,0,image_battle.width(),image_battle.height()),image_battle);
    else painter->drawImage(QRectF(0,0,image.width(),image.height()),image);
    painter->setBrush(QColor(0,160,230));
    painter->drawRect(std::max(0, (image.width() - 60) / 2), image.height(), std::max(0, 60 * hp / maxhp), 5);
}

void Unit::advance()
{
    update();
}
