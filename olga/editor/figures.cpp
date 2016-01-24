#include "figures.h"

#include <QDebug>

#include <cmath>

Figure::~Figure()
{
    qDebug() << "~Figure";
}

Figure::Figure(const QString &name_, QString color_) :
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

QString Figure::color() const
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
    strs << name << QString::number(x) << QString::number(y) << col << QString::number(angle);
    return strs;
}

Circle::Circle(const QString &name_, QString color_, int d_) :
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

Polygon Circle::points()
{
    QPoint center = pos() + QPoint(d / 2, d / 2);

    Polygon p;
    double s = 1.0 / d;
    for (double a = 0; a < 2 * 3.141592653589793238462643383279502884; a += s) {
        double x1 = d * std::cos(a) / 2 + center.x();
        double y1 = d * std::sin(a) / 2 + center.y();
        p.append(QPoint(x1, y1));
    }
    return p;
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

Rect::Rect(const QString &name_, QString color_, int w_, int h_) :
    Figure(name_, color_),
    w(w_),
    h(h_)
{

}

Rect::~Rect()
{
    qDebug() << "~Rect";
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

Polygon Rect::points()
{
    Polygon p;
    p.push_back(pos());
    p.push_back(pos() + QPoint(w, 0));
    p.push_back(pos() + QPoint(w, h));
    p.push_back(pos() + QPoint(0, h));
    return p;
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

Triangle::Triangle(const QString &name_, QString color_, QPoint a, QPoint b, QPoint c) :
    Figure(name_, color_)
{
    a_ = a;
    b_ = b;
    c_ = c;
}

Triangle::~Triangle()
{
    qDebug() << "~Triangle";
}

Polygon Triangle::points()
{
    Polygon p;
    p.push_back(a_ + pos());
    p.push_back(b_ + pos());
    p.push_back(c_ + pos());
    return p;
}

void Triangle::load(const QStringList &strs)
{
    Figure::load(strs);
    a_.setX(strs[6].toInt());
    a_.setY(strs[7].toInt());
    b_.setX(strs[8].toInt());
    b_.setY(strs[9].toInt());
    c_.setX(strs[10].toInt());
    c_.setY(strs[11].toInt());
}

QStringList Triangle::save()
{
    QStringList strs;
    strs << "T" << Figure::save()
         << QString::number(a_.x()) << QString::number(a_.y())
         << QString::number(b_.x()) << QString::number(b_.y())
         << QString::number(c_.x()) << QString::number(c_.y());
    return strs;
}

QRect Triangle::rect()
{
    int min_x = std::min(std::min(a_.x(), b_.x()), c_.x());
    int max_x = std::max(std::max(a_.x(), b_.x()), c_.x());
    int min_y = std::min(std::min(a_.y(), b_.y()), c_.y());
    int max_y = std::max(std::max(a_.y(), b_.y()), c_.y());
    QRect rect(min_x, min_y, max_x - min_x, max_y - min_y);
    rect.translate(pos());
    return rect;
}
