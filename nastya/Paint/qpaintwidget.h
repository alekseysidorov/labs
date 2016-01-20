#ifndef QPAINTWIDGET_H
#define QPAINTWIDGET_H

#include <QWidget>
#include <QString>
#include "figures.h"
#include <QSet>
#include <QPainter>


class QPaintEvent;

class QPaintWidget : public QWidget
{
    Q_OBJECT
public:

    QPaintWidget(QWidget * parent = 0);
    void paintEvent(QPaintEvent *);

    QList<Figure*> figures;
    QList<Figure*> onFigures;

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *);
    ~QPaintWidget();

    // QWidget interface
protected:
    void mouseMoveEvent(QMouseEvent *mou);
private:
    QPoint p;
public:
    int pr = 117;
    void upupdate();

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *ke);
};

#endif // QPAINTWIDGET_H
