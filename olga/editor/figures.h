#ifndef FIGURES_H
#define FIGURES_H
#include <QWidget>
#include <QColor>
#include <QString>

struct Figure
{
    QString name;
    int x;
    int y;
    QColor color;
    double angle;

    virtual void paint(QWidget *wgt) = 0;

    virtual void fromString(const QStringList &strs);
    virtual QStringList toString();
    virtual QRect rect() = 0;
    virtual ~Figure();
};

struct Circle : Figure
{
    int d;

    void paint(QWidget *wgt);

    void fromString(const QStringList &string);
    QStringList toString();
    QRect rect();
};

struct Rect : Figure
{
    int w;
    int h;

    void paint(QWidget *wgt);

    void fromString(const QStringList &strs);
    QStringList toString();
    QRect rect();
};

struct Triangle : Figure
{
    int x2;
    int y2;
    int x3;
    int y3;

    void paint(QWidget *wgt);

    void fromString(const QStringList &strs);
    QStringList toString();
    QRect rect();
};

#endif // FIGURES_H
