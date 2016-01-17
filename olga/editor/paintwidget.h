#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H
#include <QWidget>
#include "container.h"

struct Figure;

class PaintWidget : public QWidget
{
public:
    PaintWidget(QWidget *parent = 0);
    ~PaintWidget();

    void load(const QString &fileName);
    void save(const QString &fileName);
protected:
    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
private:
    Container container;
    QList<Figure*> selectedFigures;
    QPoint oldPos;
};

#endif // PAINTWIDGET_H
