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

    virtual void paint(QWidget *wgt) const = 0;

    virtual void fromString(const QStringList &strs);
    virtual QStringList toString() const;
    virtual ~Figure();
};

struct Circle : Figure
{
    int r;

    void paint(QWidget *wgt) const;

    void fromString(const QStringList &string);
    QStringList toString() const;
};

struct Rect : Figure
{
    int w;
    int h;

    void paint(QWidget *wgt) const;

    void fromString(const QStringList &strs);
    QStringList toString() const;
};

struct Triangle : Figure
{
    int x2;
    int y2;
    int x3;
    int y3;

    void paint(QWidget *wgt) const;

    void fromString(const QStringList &strs);
    QStringList toString() const;
};

#endif // FIGURES_H
