#include "figures.h"

#include <QPainter>
#include <QDebug>

#include <cmath>

Figure::~Figure()
{
    qDebug() << "~Figure";
}

Figure::Figure(const QString &name_, QColor color_) :
    name(name_),
    col(color_),
    x(0),
    y(0),
    angle(0)
{

}

void Figure::setPos(const QPoint &pos)
{
    x = pos.x();
    y = pos.y();
}

QPoint Figure::pos() const
{
    return QPoint(x, y);
}

void Figure::setRotation(double angle_)
{
    angle = angle_;
}

double Figure::rotation() const
{
    return angle;
}

QColor Figure::color() const
{
    return col;
}

void Figure::load(const QStringList &strs)
{
    name = strs[1];
    x = strs[2].toInt();
    y = strs[3].toInt();
    col = strs[4];
    angle = strs[5].toDouble();
}

QStringList Figure::save()
{
    QStringList strs;
    strs << name << QString::number(x) << QString::number(y) << col.name() << QString::number(angle);
    return strs;
}

Circle::Circle(const QString &name_, QColor color_, int d_) :
    Figure(name_, color_),
    d(d_)
{

}

void Circle::setDiameter(int d_)
{
    d = d_;
}

int Circle::diameter() const
{
    return d;
}

void Circle::paint(QPainter *p)
{
    p->setPen(color());
    p->drawEllipse(pos().x(), pos().y(), d, d);
}

void Circle::load(const QStringList &strs)
{
    Figure::load(strs);
    d = strs[6].toInt();
}

Circle::~Circle()
{
    qDebug() << "~Circle";
}

QStringList Circle::save()
{
    QStringList strs;
    strs << "C" << Figure::save() << QString::number(d);
    return strs;
}

QRect Circle::rect()
{
    return QRect(pos().x(), pos().y(), d, d);
}

Rect::Rect(const QString &name_, QColor color_, int w_, int h_) :
    Figure(name_, color_),
    w(w_),
    h(h_)
{

}

void Rect::setSize(QSize size)
{
    w = size.width();
    h = size.height();
}

QSize Rect::size() const
{
    return QSize(w, h);
}

void Rect::paint(QPainter *p)
{    
    p->setPen(color());
    p->translate(pos().x() + size().width()/2, pos().y() + size().height()/2);
    p->rotate(rotation());
    p->drawRect(-w/2, -h/2, w, h);
}

void Rect::load(const QStringList &strs)
{
    Figure::load(strs);
    w = strs[6].toInt();
    h = strs[7].toInt();
}

QStringList Rect::save()
{
    QStringList strs;
    strs << "R" << Figure::save() << QString::number(w) << QString::number(h);
    return strs;
}

QRect Rect::rect()
{
    return QRect(pos().x(), pos().y(), w, h);
}

Triangle::Triangle(const QString &name_, QColor color_, QPoint a, QPoint b) :
    Figure(name_, color_)
{
    x2 = a.x();
    y2 = a.y();
    x3 = b.x();
    y3 = b.y();
}

void Triangle::paint(QPainter *p)
{
    QPoint points[3] = {
        pos(),
        QPoint(x2, y2),
        QPoint(x3, y3),
    };

    p->setPen(color());
    p->drawPolygon(points, 3);
}

void Triangle::load(const QStringList &strs)
{
    Figure::load(strs);
    x2 = strs[6].toInt();
    y2 = strs[7].toInt();
    x3 = strs[8].toInt();
    y3 = strs[9].toInt();
}

QStringList Triangle::save()
{
    QStringList strs;
    strs << "T" << Figure::save() << QString::number(x2) << QString::number(y2)
         << QString::number(x3) << QString::number(y3);
    return strs;
}

QRect Triangle::rect()
{
    int min_x = std::min(std::min(pos().x(), x2), x3);
    int max_x = std::max(std::max(pos().x(), x2), x3);
    int min_y = std::min(std::min(pos().y(), y2), y3);
    int max_y = std::max(std::max(pos().y(), y2), y3);

    return QRect(min_x, min_y, max_x - min_x, max_y - min_y);
}
