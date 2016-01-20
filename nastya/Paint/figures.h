#ifndef FIGURES_H
#define FIGURES_H
#include <QString>
#include <QWidget>
#include <QDir>
#include <QRect>

class QPaintWidget;


class Figure
{
public:
    QString t;
    Figure();
    int x;
    int y;
    qreal a;
    QString color;
    QString name;
    virtual void paintEv(QPainter &p) = 0;
    virtual void paint(QPaintWidget *p) = 0;
    virtual void save(QString d) = 0;
    virtual bool pop(int mx, int my) = 0;
    virtual QRect rectt() = 0;
    virtual ~Figure();
};

class Circle :public Figure
{
public:
    Circle(int x1, int y1, int r1, QString color1, QString name1);
    QRect rectt();
    bool pop(int mx, int my);
    void paintEv(QPainter &p);
    void paint(QPaintWidget *p);
    void save(QString d);
    int r;
};


class Rectanglee :public Figure
{
public:
    QRect rectt();
    bool pop(int mx, int my);
    Rectanglee(int x1, int y1, int w1, int h1, QString color1, QString name1);
    void paintEv(QPainter &p);
    void paint(QPaintWidget *wgt);
    void save(QString d);
    int w;
    int h;
};

#endif // FIGURES_H
