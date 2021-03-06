#ifndef QPAINTWIDGET_H
#define QPAINTWIDGET_H

#include <QString>
#include "figures.h"
#include <QSet>
#include <QWidget>
#include "figlibrary.h"

class QPaintEvent;

class QPaintWidget : public QWidget
{
    Q_OBJECT
public:

    QPaintWidget(QWidget * parent = 0);
    void paintEvent(QPaintEvent *);

    void addFig(Figure *);
    void download(QString ss);
    void save(QString dd);
    void clear();

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *);
    ~QPaintWidget();

    // QWidget interface
protected:
    void mouseMoveEvent(QMouseEvent *mou);
private:
    QPoint p;
    FigLibrary figa;
    QList<Figure*> onFigures;
public:
    int pr = 117;
    void upupdate();

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *ke);
};

#endif // QPAINTWIDGET_H
