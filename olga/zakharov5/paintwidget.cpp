#include "paintwidget.h"

#include <QPainter>

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{

}

void PaintWidget::paint(const QImage &image)
{
    this->image = image;
    update();
}

void PaintWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawImage(0, 0, image);
}

