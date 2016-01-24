#ifndef FIGURES_H
#define FIGURES_H
#include <QString>
#include <QRect>
#include <QVector>

typedef QVector<QPoint> Polygon;

class QPainter;
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

    virtual Polygon points() = 0;

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

    Polygon points();

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

    Polygon points();

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

    Polygon points();

    void load(const QStringList &strs);
    QStringList save();
    QRect rect();
};

#endif // FIGURES_H
