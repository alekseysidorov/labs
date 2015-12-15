#include "paintwidget.h"

#include <QPainter>

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{

}

void PaintWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QPen pen;
    pen.setColor("green");
    p.setPen(pen);
    p.drawRect(167, 194, 26, 49);
    pen.setColor("violet");
    p.setPen(pen);
    p.drawEllipse(150, 150, 27, 85);
    for (int i = 0; i < size().width(); i++) {
        for (int j = 0; j < size().height(); j++) {
            pen.setColor(qrand());
            p.setPen(pen);
            p.drawPoint(i, j);
        }
    }

}

