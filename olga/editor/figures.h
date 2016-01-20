#ifndef FIGURES_H
#define FIGURES_H
#include <QColor>
#include <QString>
#include <QRect>

class QPainter;

class Figure
{
    QString name;
    int x;
    int y;
    QColor col;
    double angle;
public:
    Figure(const QString &name_, QColor color_);
    void setPos(const QPoint &pos);
    QPoint pos() const;
    void setRotation(double angle);
    double rotation() const;
    QColor color() const;

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
    Circle(const QString &name_, QColor color_, int d_);

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
    Rect(const QString &name_, QColor color_, int w_, int h_);

    void setSize(QSize size);
    QSize size() const;

    void paint(QPainter *p);

    void load(const QStringList &strs);
    QStringList save();
    QRect rect();
};

class Triangle : public Figure
{
    int x2;
    int y2;
    int x3;
    int y3;
public:
    Triangle(const QString &name_, QColor color_, QPoint a, QPoint b);

    void paint(QPainter *p);

    void load(const QStringList &strs);
    QStringList save();
    QRect rect();
};

#endif // FIGURES_H
