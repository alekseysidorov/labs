#include "circle.h"
#include "qpaintwidget.h"

Circle::Circle(int x, int y, int radius, QString color)
{
    Cx = x;
    Cy = y;
    rad = radius;
    col = color;
}

void Circle::topaint()
{
    void QPaintWidget::paintEvent(QPaintEvent *) {
        QPainter p(this); // Создаём новый объект рисовальщика
        p.setPen(QPen(Qt::red,1,Qt::SolidLine)); // Настройки рисования
        p.drawLine(0,0,width(),height()); // Рисование линии
        p.drawEllipse(0, 0, 20, 20);
}

