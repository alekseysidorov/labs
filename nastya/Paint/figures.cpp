#include "figures.h"
#include <QDir>
#include <QSettings>
#include <qpaintwidget.h>
#include <QPainter>


Circle::Circle(int x1, int y1, int r1, QString color1, QString name1)
{
    t = "circle";
    x = x1;
    y = y1;
    r = r1;
    color = color1;
    name = name1;
}

QRect Circle::rectt()
{
    QRect r1(x, y, r, r);
    return r1;
}

bool Circle::pop(int mx, int my)
{
   if ((mx > x) && (mx < x + r) &&
                    (my > y) && (my < y + r))
            return 1;
    return 0;
}

void Circle::paintEv(QPainter &p)
{
        if (color == "red")
        p.setPen(QPen(Qt::red,1,Qt::SolidLine));
        if (color == "blue")
        p.setPen(QPen(Qt::blue,1,Qt::SolidLine));
        if (color == "black")
        p.setPen(QPen(Qt::black,1,Qt::SolidLine));
        if (color == "green")
        p.setPen(QPen(Qt::green,1,Qt::SolidLine));
        if (color == "yellow")
        p.setPen(QPen(Qt::yellow,1,Qt::SolidLine));
        if (color == "gray")
        p.setPen(QPen(Qt::gray,1,Qt::SolidLine));
        p.drawEllipse(x, y, r, r);
}

void Circle::paint(QPaintWidget *p)
{
    p->figures.append(this);
}

void Circle::save(QString d)
{
    QSettings param(d, QSettings::Format::IniFormat);
    param.setIniCodec("UTF8");
    param.clear();
    param.setValue("Name", name);
    param.setValue("Color", color);
    param.setValue("Radius", QString::number(r));
    param.setValue("X", QString::number(x));
    param.setValue("Y", QString::number(y));
    param.setValue("Type", t);
}


QRect Rectanglee::rectt()
{
    QRect r(x - 3, y - 3, w + 6, h + 6);
    return r;
}

bool Rectanglee::pop(int mx, int my)
{
    if ((mx > x) && (mx < x + w) &&
            (my > y) && (my < y + h))
        return 1;
    return 0;
}

Rectanglee::Rectanglee(int x1, int y1, int w1, int h1, QString color1, QString name1)
{
    t = "rectangle";
    x = x1;
    y = y1;
    w = w1;
    h = h1;
    color = color1;
    name = name1;
    a = 0;
}

void Rectanglee::paintEv(QPainter &p)
{
    if (color == "red")
    p.setPen(QPen(Qt::red,1,Qt::SolidLine));
    if (color == "blue")
    p.setPen(QPen(Qt::blue,1,Qt::SolidLine));
    if (color == "black")
    p.setPen(QPen(Qt::black,1,Qt::SolidLine));
    if (color == "green")
    p.setPen(QPen(Qt::green,1,Qt::SolidLine));
    if (color == "yellow")
    p.setPen(QPen(Qt::yellow,1,Qt::SolidLine));
    if (color == "gray")
    p.setPen(QPen(Qt::gray,1,Qt::SolidLine));
    p.translate(x, y);
    p.rotate(a);
    p.drawRect(0, 0, w, h);
    p.rotate(-a);
    p.translate(-x, -y);
}

void Rectanglee::paint(QPaintWidget *wgt)
{
    wgt->figures.append(this);
}

void Rectanglee::save(QString d)
{
    QSettings param1(d, QSettings::Format::IniFormat);
    param1.setIniCodec("UTF8");
    param1.clear();
    param1.setValue("Name", name);
    param1.setValue("Color", color);
    param1.setValue("Width", QString::number(w));
    param1.setValue("Height", QString::number(h));
    param1.setValue("X", QString::number(x));
    param1.setValue("Y", QString::number(y));
    param1.setValue("Type", t);
}


Figure::Figure()
{

}


Figure::~Figure()
{

}
