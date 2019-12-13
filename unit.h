#ifndef UNIT_H
#define UNIT_H

#include <QObject>
#include <QGraphicsItem>
#include <QRectF>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QTimer>
#include <QDebug>

class Unit : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Unit(int x, int y, int atk, int def, int hp, QString name, QObject *parent = nullptr);
    void modifyHp(int val);
    int getHp();
    int getx();
    int gety();

protected:
    QRectF boundingRect()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:

public slots:
    virtual void advance();

protected:
    int x, y, maxhp, atk, def, hp;
    QImage image, image_battle;
    int imageNo;
    bool battle;
    int time_cnt;
};

#endif // UNIT_H
