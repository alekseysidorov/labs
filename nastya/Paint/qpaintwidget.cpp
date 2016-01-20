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

    for (int i = 0; i < liba.figss().size(); ++i)
        liba.figss()[i]->paintEv(op);

    op.setPen(QPen(Qt::gray,1,Qt::DotLine));
    for (int i = 0; i < onFigures.size(); ++i)
    {
         op.drawRect(onFigures[i]->rectt());
    }
}

void QPaintWidget::addFig(Figure *fig)
{
    liba.add(fig);
    update();
}

void QPaintWidget::download(QString ss)
{
    liba.load(ss);
    update();
}

void QPaintWidget::save(QString dd)
{
    liba.save(dd);
}

void QPaintWidget::clear()
{
    onFigures.clear();
    liba.clear();
    update();
}

void QPaintWidget::mousePressEvent(QMouseEvent *mo)
{
    int k = 0;
    for (int i = 0; i < liba.figss().size(); ++i)
        if (liba.figss()[i]->pop(mo->pos().x(), mo->pos().y()) &&
                (mo->button() == Qt::LeftButton))
        {
            k = 117;
            if (!onFigures.contains(liba.figss()[i]))
            onFigures.append(liba.figss()[i]);
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
        addFig(hh);
        this->update();
    }
    if (mo->button() == Qt::LeftButton)
    {
        Rectanglee *hi = new Rectanglee(mo->pos().x(), mo->pos().y(), 100, 100, "black", "wwoy");
        addFig(hi);
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
        onFigures[i]->moveto(onFigures[i]->x() + pi.x(), onFigures[i]->y() + pi.y());
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
        if (onFigures[i]->typ() == "rectangle" || onFigures[i]->typ() == "star")
        {
    if (ke->key() == Qt::Key_Left) onFigures[i]->rotat(-2);
    if (onFigures[i]->angl() < -360) onFigures[i]->rotat(360);
        }
    }
    for (int i = 0; i < onFigures.size(); ++i)
    {
        if (onFigures[i]->typ() == "rectangle" || onFigures[i]->typ() == "star")
        {
    if (ke->key() == Qt::Key_Right) onFigures[i]->rotat(2);
    if (onFigures[i]->angl() > 360) onFigures[i]->rotat(-360);
    }
    }
    if (ke->key() == Qt::Key_Space)
        pr = 117;
    this->update();
}
