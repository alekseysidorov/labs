#include "thread.h"
#include "figures.h"
#include <random>
#include "mainwindow.h"
#include <QTime>

Thread::Thread(QPaintWidget *wgtt)
{
    wgt = wgtt;
    connect(this, &Thread::updatePaint, wgt, &QPaintWidget::upupdate);
}

void Thread::run()
{
    while (1)
    if (wgt->pr == 0)
    {
    QTime t = QTime::currentTime();
    qsrand((uint)t.msec());
    uint f = qrand() % 2;
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
        k->paint(wgt);
        updatePaint();
        msleep(500);
    }
    else
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
        k->paint(wgt);
        updatePaint();
        msleep(500);
    }
}
}

