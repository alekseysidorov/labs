#ifndef FIGURES_H
#define FIGURES_H
#include <QColor>
#include <QString>
#include <QRect>

class QPainter;

//class Point
//{
//    int x_;
//    int y_;
//public:
//    Point(int x = 0, int y = 0);

//    void setX(int x)
//    {
//        x_ = x;
//    }
//    int x() const
//    {
//        return x_;
//    }
//    void setY(int y)
//    {
//        y_ = y;
//    }
//    int y() const
//    {
//        return y_;
//    }
//};
//typedef QList<Point> Points;

class Figure
{
    QString name;
    int x;
    int y;
    QString col;
    double angle;
public:
    Figure(const QString &name_, QString color_);
    void setPos(const QPoint &pos);
    QPoint pos() const;
    void setRotation(double angle);
    double rotation() const;
    QString color() const;

    virtual void paint(QPainter *p) = 0;

    virtual void load(const QStringList &strs);
    virtual QStringList save();
    virtual QRect rect() = 0;
    virtual ~Figure();
};

class Circle : public Figure
{
    int d;
public:
    Circle(const QString &name_, QString color_, int d_);

    void setDiameter(int d_);
    int diameter() const;

    void paint(QPainter *p);

    void load(const QStringList &string);
    ~Circle();
    QStringList save();
    QRect rect();
};

class Rect : public Figure
{
    int w;
    int h;
public:
    Rect(const QString &name_, QString color_, int w_, int h_);
    ~Rect();

    void setSize(QSize size);
    QSize size() const;

    void paint(QPainter *p);

    void load(const QStringList &strs);
    QStringList save();
    QRect rect();
};

class Triangle : public Figure
{
    QPoint a_;
    QPoint b_;
    QPoint c_;
public:
    Triangle(const QString &name_, QString color_, QPoint a, QPoint b, QPoint c);
    ~Triangle();

    void paint(QPainter *p);

    void load(const QStringList &strs);
    QStringList save();
    QRect rect();
};

#endif // FIGURES_H
