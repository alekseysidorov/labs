#include "figures.h"
#include <QDir>
#include <QSettings>
#include <qpaintwidget.h>
#include <QPainter>

#include <cmath>
#include <cstdlib>

Circle::Circle(int x1, int y1, int r1, QString color1, QString name1) :
    Figure(name1, color1, "circle")
{
    moveto(x1, y1);
    r = r1;
}

QRect Circle::rectt()
{
    QRect r1(x_, y_, r, r);
    return r1;
}

bool Circle::pop(int mx, int my)
{
   if ((mx > x_) && (mx < x_ + r) &&
                    (my > y_) && (my < y_ + r))
            return 1;
    return 0;
}

void Circle::paintEv(QPainter &p)
{
        if (col() == "red")
        p.setPen(QPen(Qt::red,1,Qt::SolidLine));
        if (col() == "blue")
        p.setPen(QPen(Qt::blue,1,Qt::SolidLine));
        if (col() == "black")
        p.setPen(QPen(Qt::black,1,Qt::SolidLine));
        if (col() == "green")
        p.setPen(QPen(Qt::green,1,Qt::SolidLine));
        if (col() == "yellow")
        p.setPen(QPen(Qt::yellow,1,Qt::SolidLine));
        if (col() == "gray")
        p.setPen(QPen(Qt::gray,1,Qt::SolidLine));
        p.drawEllipse(x_, y_, r, r);
}

void Circle::save(QString d)
{
    QSettings param(d, QSettings::Format::IniFormat);
    param.setIniCodec("UTF8");
    param.clear();
    param.setValue("Name", nam());
    param.setValue("Color", col());
    param.setValue("Radius", QString::number(r));
    param.setValue("X", QString::number(x_));
    param.setValue("Y", QString::number(y_));
    param.setValue("Type", typ());
}


QRect Rectanglee::rectt()
{
    QRect r(x_ - 3, y_ - 3, w + 6, h + 6);
    return r;
}

bool Rectanglee::pop(int mx, int my)
{
    if ((mx > x_) && (mx < x_ + w) &&
            (my > y_) && (my < y_ + h))
        return 1;
    return 0;
}

Rectanglee::Rectanglee(int x1, int y1, int w1, int h1, QString color1, QString name1) :
    Figure(name1, color1, "rectangle")
{
    moveto(x1, y1);
    w = w1;
    h = h1;
}

void Rectanglee::paintEv(QPainter &p)
{
    if (col() == "red")
    p.setPen(QPen(Qt::red,1,Qt::SolidLine));
    if (col() == "blue")
    p.setPen(QPen(Qt::blue,1,Qt::SolidLine));
    if (col() == "black")
    p.setPen(QPen(Qt::black,1,Qt::SolidLine));
    if (col() == "green")
    p.setPen(QPen(Qt::green,1,Qt::SolidLine));
    if (col() == "yellow")
    p.setPen(QPen(Qt::yellow,1,Qt::SolidLine));
    if (col() == "gray")
    p.setPen(QPen(Qt::gray,1,Qt::SolidLine));
    p.translate(x_, y_);
    p.rotate(a);
    p.drawRect(0, 0, w, h);
    p.rotate(-a);
    p.translate(-x_, -y_);
}

void Rectanglee::save(QString d)
{
    QSettings param1(d, QSettings::Format::IniFormat);
    param1.setIniCodec("UTF8");
    param1.clear();
    param1.setValue("Name", nam());
    param1.setValue("Color", col());
    param1.setValue("Width", QString::number(w));
    param1.setValue("Height", QString::number(h));
    param1.setValue("X", QString::number(x_));
    param1.setValue("Y", QString::number(y_));
    param1.setValue("Type", typ());
}


Figure::Figure(QString n, QString col, QString ty) : name(n), color(col), t(ty)
{
    a = 0;
}


Figure::~Figure()
{

}

int Figure::x() { return x_; }

int Figure::y() { return y_; }

void Figure::setAngl(qreal ang)
{
    a = ang;
}

qreal Figure::angl()
{
    return a;
}

void Figure::rotat(qreal ang)
{
    a += ang;
}

QString Figure::typ()
{
    return t;
}

void Figure::moveto(int x, int y)
{
    this->x_ = x;
    this->y_ = y;
}

QString Figure::col()
{
    return color;
}

QString Figure::nam()
{
    return name;
}

Star::Star(int x1, int y1, QString col1, QString name1, int md) :
    Figure(name1, col1, "star")
{
    moveto(x1, y1);
    r = md;
}

void Star::paintEv(QPainter &p)
{
    QPolygonF sp;
    sp.append(QPointF(r, 0.5 * r));
    for (int i = 1; i < 5; ++i)
        sp.append(QPointF(r * (0.5 + 0.5 * std::cos(0.8 * i * 3.14)), r * (0.5 + 0.5 * std::sin(0.8 * i * 3.14))));

    if (col() == "red")
    p.setPen(QPen(Qt::red,1,Qt::SolidLine));
    if (col() == "blue")
    p.setPen(QPen(Qt::blue,1,Qt::SolidLine));
    if (col() == "black")
    p.setPen(QPen(Qt::black,1,Qt::SolidLine));
    if (col() == "green")
    p.setPen(QPen(Qt::green,1,Qt::SolidLine));
    if (col() == "yellow")
    p.setPen(QPen(Qt::yellow,1,Qt::SolidLine));
    if (col() == "gray")
    p.setPen(QPen(Qt::gray,1,Qt::SolidLine));

    p.translate(x(), y());
    p.rotate(a);
    p.drawPolygon(sp);
    p.rotate(-a);
    p.translate(-x(), -y());
}

void Star::save(QString d)
{
    QSettings param(d, QSettings::Format::IniFormat);
    param.setIniCodec("UTF8");
    param.clear();
    param.setValue("Name", nam());
    param.setValue("Color", col());
    param.setValue("Diameter", QString::number(r));
    param.setValue("X", QString::number(x_));
    param.setValue("Y", QString::number(y_));
    param.setValue("Type", typ());
}

bool Star::pop(int mx, int my)
{
    if ((mx > x_) && (mx < (x_ + r)) &&
                     (my > y_) && (my < (y_ + r)))
             return 1;
     return 0;
}

QRect Star::rectt()
{
    return QRect(x_, y_, r, r);
}
