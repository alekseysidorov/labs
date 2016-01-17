#include "figures.h"

#include <QPainter>
#include <QDebug>

#include <cmath>

Figure::~Figure()
{
    qDebug() << "~Figure";
}

void Figure::load(const QStringList &strs)
{
    name = strs[1];
    x = strs[2].toInt();
    y = strs[3].toInt();
    color = strs[4];
    angle = strs[5].toDouble();
}

QStringList Figure::save()
{
    QStringList strs;
    strs << name << QString::number(x) << QString::number(y) << color.name() << QString::number(angle);
    return strs;
}

void Circle::paint(QPainter *p)
{
    p->setPen(color);
    p->drawEllipse(x, y, d, d);
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
    return QRect(x, y, d, d);
}

void Rect::paint(QPainter *p)
{
    p->setPen(color);
    p->translate(x + w/2, y + h/2);
    p->rotate(angle);
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
    return QRect(x, y, w, h);
}

void Triangle::paint(QPainter *p)
{
    QPoint points[3] = {
        QPoint(x, y),
        QPoint(x2, y2),
        QPoint(x3, y3),
    };

    p->setPen(color);
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
    int min_x = std::min(std::min(x, x2), x3);
    int max_x = std::max(std::max(x, x2), x3);
    int min_y = std::min(std::min(y, y2), y3);
    int max_y = std::max(std::max(y, y2), y3);

    return QRect(min_x, min_y, max_x - min_x, max_y - min_y);
}
