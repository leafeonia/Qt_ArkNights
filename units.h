#ifndef UNITS_H
#define UNITS_H

#endif // UNITS_H

#include <QLabel>
#include <QImage>
#include <QPainter>
#include <QGraphicsPixmapItem>

class Unit: public QGraphicsPixmapItem{
public:
    Unit(QWidget* pthis){
        posx = 300;
        posy = 150;
        label = new QLabel(pthis);
        label->setGeometry(posx, posy, 120, 150);
        label->setAlignment(Qt::AlignCenter);
        QImage image(":/resource/texas_model.png");
        QPainter p;
        p.begin(&image);
        p.setCompositionMode(QPainter::CompositionMode_DestinationIn);
        p.fillRect(image.rect(), QColor(0, 0, 0, 50));
        p.end();
        label->setPixmap(QPixmap::fromImage(image));
//        QPixmap image = QPixmap(":/resource/texas_model.png");
//        label->setPixmap(image);
        label->show();
    }

private:
    int posx, posy;
    QLabel* label;
};
