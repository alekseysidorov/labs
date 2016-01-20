#include "qpaintwidget.h"

#include <QPainter>
#include <QSettings>
#include <QDir>
#include <QMouseEvent>


QPaintWidget::QPaintWidget(QWidget * parent) : QWidget(parent)
{
setFocus();
grabKeyboard();
}

void QPaintWidget::paintEvent(QPaintEvent *)
{
    QPainter op(this);

    for (int i = 0; i < figures.size(); ++i)
        figures[i]->paintEv(op);

    op.setPen(QPen(Qt::gray,1,Qt::DotLine));
    for (int i = 0; i < onFigures.size(); ++i)
    {
         op.drawRect(onFigures[i]->rectt());
    }
}

void QPaintWidget::mousePressEvent(QMouseEvent *mo)
{
    int k = 0;
    for (int i = 0; i < figures.size(); ++i)
        if (figures[i]->pop(mo->pos().x(), mo->pos().y()) &&
                (mo->button() == Qt::LeftButton))
        {
            k = 117;
            if (!onFigures.contains(figures[i]))
            onFigures.append(figures[i]);
            update();
        }

    for (int i = 0; i < onFigures.size(); ++i)
        if (onFigures[i]->pop(mo->pos().x(), mo->pos().y()) &&
                (mo->button() == Qt::RightButton))
        {
            k = 117;
            onFigures.removeAt(i);
            --i;
            update();
        }

    if (k == 0)
    {
    if (mo->button() == Qt::RightButton)
    {
        Circle *hh = new Circle(mo->pos().x(), mo->pos().y(), 100, "red", "wwo");
        hh->paint(this);
        this->update();
    }
    if (mo->button() == Qt::LeftButton)
    {
        Rectanglee *hi = new Rectanglee(mo->pos().x(), mo->pos().y(), 100, 100, "black", "wwoy");
        hi->paint(this);
        this->update();
    }
    }
    else p = mo->pos();
}

QPaintWidget::~QPaintWidget()
{
}

void QPaintWidget::mouseMoveEvent(QMouseEvent *mou)
{
    QPoint pi = mou->pos() - p;
    for (int i = 0; i < onFigures.size(); ++i)
    {
        onFigures[i]->x += pi.x();
        onFigures[i]->y += pi.y();
    }
    p = mou->pos();
    this->update();
}

void QPaintWidget::upupdate()
{
    this->update();
}


void QPaintWidget::keyPressEvent(QKeyEvent *ke)
{
    for (int i = 0; i < onFigures.size(); ++i)
    {
        if (onFigures[i]->t == "rectangle")
        {
    if (ke->key() == Qt::Key_Left) onFigures[i]->a -= 2;
    if (onFigures[i]->a < -360) onFigures[i]->a += 360;
        }
    }
    for (int i = 0; i < onFigures.size(); ++i)
    {
        if (onFigures[i]->t == "rectangle")
        {
    if (ke->key() == Qt::Key_Right) onFigures[i]->a += 2;
    if (onFigures[i]->a > 360) onFigures[i]->a -= 360;
    }
    }
    if (ke->key() == Qt::Key_Space)
        pr = 117;
    this->update();
}
