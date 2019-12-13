#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "units.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    timer->start(2000);
    connect(timer, SIGNAL(timeout()), this, SLOT(Timesignal()));
//    this->setMinimumSize(1414,695);
//    painter = new QPainter(this);
    Unit* unit = new Unit(this);
}

//MainWindow::paintEvent(QPaintEvent *event){
//    QRectF target(0,0, this->width(), this->width());
//    QRectF source(0,0, this->width(), this->width());
//    QPixmap pixmap_background(":/resource/bg.jpg");
//    painter->drawPixmap(target, pixmap_background, source);

//}

void MainWindow::Timesignal(){
//    qDebug() << "Signal" << std::endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}
