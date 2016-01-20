#ifndef FIGURES_H
#define FIGURES_H
#include <QString>
#include <QWidget>
#include <QDir>
#include <QRect>

class Figure
{
public:
    Figure(QString n, QString col, QString ty);

    virtual void paintEv(QPainter &p) = 0;
    virtual void save(QString d) = 0;
    virtual bool pop(int mx, int my) = 0;
    virtual QRect rectt() = 0;
    virtual ~Figure();

    int x();
    int y();

    void setAngl(qreal ang);
    qreal angl();
    void rotat(qreal ang);
    QString typ();
    void moveto(int x, int y);
    QString col();
    QString nam();
private:
    QString color;
    QString name;
    QString t;
protected:
    int x_;
    int y_;
    qreal a;
};

class Circle :public Figure
{
public:
    Circle(int x1, int y1, int r1, QString color1, QString name1);
    QRect rectt();
    bool pop(int mx, int my);
    void paintEv(QPainter &p);
    void save(QString d);
protected:
    int r;
};


class Rectanglee :public Figure
{
public:
    QRect rectt();
    bool pop(int mx, int my);
    Rectanglee(int x1, int y1, int w1, int h1, QString color1, QString name1);
    void paintEv(QPainter &p);
    void save(QString d);
protected:
    int w;
    int h;
};

class Star :public Figure
{
public:
    Star(int x1, int y1, QString col1, QString name1, int r);

    // Figure interface
public:
    void paintEv(QPainter &p);
    void save(QString r);
    bool pop(int mx, int my);
    QRect rectt();
protected:
    int r;
};

#endif // FIGURES_H
