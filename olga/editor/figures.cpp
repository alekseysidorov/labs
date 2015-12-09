#include "figures.h"

#include <QPainter>

Figure::~Figure()
{

}

void Figure::fromString(const QStringList &strs)
{
    name = strs[1];
    x = strs[2].toInt();
    y = strs[3].toInt();
    color = strs[4];
}

QStringList Figure::toString() const
{
    QStringList strs;
    strs << name << QString::number(x) << QString::number(y) << color.name();
    return strs;
}

void Circle::paint(QWidget *wgt) const
{
    QPainter p(wgt);

    p.setPen(color);
    p.drawEllipse(x, y, r, r);
}

void Circle::fromString(const QStringList &strs)
{
    Figure::fromString(strs);
    r = strs[5].toInt();
}

QStringList Circle::toString() const
{
    QStringList strs;
    strs << "C" << Figure::toString() << QString::number(r);
    return strs;
}

void Rect::paint(QWidget *wgt) const
{
    QPainter p(wgt);

    p.setPen(color);
    p.drawRect(x, y, w, h);
}

void Rect::fromString(const QStringList &strs)
{
    Figure::fromString(strs);
    w = strs[5].toInt();
    h = strs[6].toInt();
}

QStringList Rect::toString() const
{
    QStringList strs;
    strs << "R" << Figure::toString() << QString::number(w) << QString::number(h);
    return strs;
}

void Triangle::paint(QWidget *wgt) const
{
    QPainter p(wgt);

    QPoint points[3] = {
        QPoint(x, y),
        QPoint(x2, y3),
        QPoint(x3, y3),
    };

    p.setPen(color);
    p.drawPolygon(points, 3);
}

void Triangle::fromString(const QStringList &strs)
{
    Figure::fromString(strs);
    x2 = strs[5].toInt();
    y2 = strs[6].toInt();
    x3 = strs[7].toInt();
    y3 = strs[8].toInt();
}

QStringList Triangle::toString() const
{
    QStringList strs;
    strs << "T" << Figure::toString() << QString::number(x2) << QString::number(y2)
         << QString::number(x3) << QString::number(y3);
    return strs;
}
