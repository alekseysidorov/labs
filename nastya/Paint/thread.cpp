#include "thread.h"
#include "figures.h"
#include <random>
#include "mainwindow.h"
#include <QTime>

Thread::Thread(QPaintWidget *wgtt, MainWindow* w1)
{
    w = w1;
    wgt = wgtt;
    connect(this, &Thread::updatePaint, wgt, &QPaintWidget::upupdate);
}

Thread::~Thread()
{
    this->quit();
    this->wait();
}

void Thread::run()
{
    while (w->Tra() == 117)
    if (wgt->pr == 0)
    {
    QTime t = QTime::currentTime();
    qsrand((uint)t.msec());
    uint f = qrand() % 3;
    if (f == 0)
    {
        uint x = qrand() % 300;
        uint y = qrand() % 300;
        uint r = qrand() % 100;
        uint c = qrand() % 4;
        QString col;
        if (c == 0) col = "green";
        else
        if (c ==  1) col = "red";
        else
        if (c == 2) col = "yellow";
        else
        col = "blue";
        uint n = qrand() % 10000;
        Circle *k = new Circle(x, y, r, col, QString::number(n));
        wgt->addFig(k);
        updatePaint();
        msleep(500);
    }
    else if (f == 1)
    {
        uint x = qrand() % 300;
        uint y = qrand() % 300;
        uint w = qrand() % 100;
        uint h = qrand() % 100;
        uint c = qrand() % 4;
        QString col;
        if (c == 0) col = "green";
        else
        if (c ==  1) col = "red";
        else
        if (c == 2) col = "yellow";
        else
        col = "blue";
        uint n = qrand() % 100000;
        Rectanglee *k = new Rectanglee(x, y, w, h, col, QString::number(n));
        wgt->addFig(k);
        updatePaint();
        msleep(500);
    } else {
        uint x = qrand() % 300;
        uint y = qrand() % 300;
        uint r = qrand() % 100;
        uint c = qrand() % 4;
        QString col;
        if (c == 0) col = "cian";
        else
        if (c ==  1) col = "red";
        else
        if (c == 2) col = "green";
        else
        col = "blue";
        uint n = qrand() % 10000;
        Star *k = new Star(x, y, col, QString::number(n), r);
        wgt->addFig(k);
        updatePaint();
        msleep(500);
    }
}
}

