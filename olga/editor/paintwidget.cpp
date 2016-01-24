#include "paintwidget.h"
#include "figures.h"
#include <cmath>

#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDebug>
#include <QMouseEvent>
#include <QPainter>

void rotatePolygon(QPolygon &points, QPoint center, double angle)
{
    double d = 3.141592653589793238462643383279502884 / 180 * angle;

    for (int i = 0; i < points.size(); ++i) {
        QPoint p = points[i];
        p -= center;

        int x = p.x();
        int y = p.y();
        p.setX(x * std::cos(d) - y * std::sin(d));
        p.setY(y * std::cos(d) + x * std::sin(d));
        p += center;
        points[i] = p;
    }
}

PaintWidget::PaintWidget(QWidget *parent) :
    QWidget(parent)
{
    QDir dir = QDir::home();
    dir.cd("Figures");

    load(dir.absoluteFilePath("library.txt"));
}

PaintWidget::~PaintWidget()
{
    QDir dir = QDir::home();
    dir.mkdir("Figures");
    dir.cd("Figures");

    save(dir.absoluteFilePath("library.txt"));
}

void PaintWidget::load(const QString &fileName)
{
    container.load(fileName);
}

void PaintWidget::save(const QString &fileName)
{
    container.save(fileName);
}

void PaintWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.save();

    for (int i = 0; i < container.figuresCount(); ++i) {
        Figure *f = container.figureAt(i);

        p.setPen(f->color());
        QPolygon po = f->points();
        rotatePolygon(po, f->rect().center(), f->rotation());
        p.drawPolygon(po);
    }
    p.restore();

    QPen pen(Qt::DashLine);
    pen.setColor("gray");
    p.setPen(pen);
    for (int i = 0; i < selectedFigures.size(); ++i) {
        QRect r = selectedFigures[i]->rect();
        r.setX(r.x() - 5);
        r.setY(r.y() - 5);
        r.setHeight(r.height() + 5);
        r.setWidth(r.width() + 5);

        p.drawRect(r);
    }
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->modifiers() & Qt::ControlModifier) {
        if (e->button() == Qt::LeftButton) {
            Rect *r = new Rect("my_rect", "blue", e->x(), e->y());
            r->setSize(QSize(100, 100));
            r->setPos(e->pos());
            container.addFigure(r);
            update();
        } else if (e->button() == Qt::RightButton) {
            Circle *c = new Circle("my_circle", "red", 100);
            c->setPos(e->pos());
            container.addFigure(c);
            update();
        } else if (e->button() == Qt::MiddleButton) {
            Triangle *t = new Triangle("my_triangle", "green", QPoint(-30, -30), QPoint(30, -30), QPoint(0, 30));
            t->setPos(e->pos());
            container.addFigure(t);
            update();
        }
    } else {
        if (e->button() == Qt::RightButton) {
            for (int i = 0; i < selectedFigures.size(); ++i) {
                QRect r = selectedFigures[i]->rect();
                if (e->x() >= r.x() && e->x() <= r.right() && e->y() >= r.y() && e->y() <= r.bottom()) {
                    selectedFigures.removeAt(i);
                }
            }
            update();
        }
    }
}

void PaintWidget::mousePressEvent(QMouseEvent *e)
{
    oldPos = e->pos();
    if (e->button() == Qt::LeftButton) {
        for (int i = 0; i < container.figuresCount(); ++i) {
            Figure *fig = container.figureAt(i);
            QRect r = fig->rect();
            if (e->x() >= r.x() && e->x() <= r.right() && e->y() >= r.y() && e->y() <= r.bottom()
                    && !selectedFigures.contains(fig)) {
                selectedFigures.append(fig);
            }
        }
        update();
    } else if (e->button() == Qt::RightButton) {
    }
}

void PaintWidget::mouseMoveEvent(QMouseEvent *e)
{
    QPoint dP = e->pos() - oldPos;
    if (e->modifiers() & Qt::ShiftModifier) {
        if (selectedFigures.size() == 1) {
            QLineF l(0, 0, dP.x(), dP.y());

            selectedFigures[0]->setRotation(l.angle());
            update();
        }
    } else {
        for (int i = 0; i < selectedFigures.size(); ++i) {
            selectedFigures[i]->setPos(selectedFigures[i]->pos() + dP);
        }
        update();
        oldPos = e->pos();
    }
}

