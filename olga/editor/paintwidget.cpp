#include "paintwidget.h"
#include "figures.h"

#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDebug>
#include <QMouseEvent>
#include <QPainter>

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
    qDeleteAll(figures);
}

void PaintWidget::load(const QString &fileName)
{
    qDebug() << "load:" << fileName;

    QFile file(fileName);
    file.open(QFile::ReadOnly|QFile::Text);
    QTextStream in(&file);

    while (!in.atEnd()) {
        QString str = in.readLine();

        QStringList strs = str.split(' ');
        QString n = strs[0];

        qDebug() << strs;

        Figure *f = 0;
        if (n == "C") f = new Circle;
        else if (n == "R") f = new Rect;
        else if (n == "T") f = new Triangle;

        if (f) {
            f->fromString(strs);
            figures.append(f);
        }
    }
}

void PaintWidget::save(const QString &fileName)
{
    QFile file(fileName);
    file.open(QFile::WriteOnly|QFile::Text);
    QTextStream out(&file);

    for (int i = 0; i < figures.size(); ++i) {
        out << figures[i]->toString().join(' ') << "\n";
    }
}

void PaintWidget::paintEvent(QPaintEvent *e)
{
    for (int i = 0; i < figures.size(); ++i) {
        figures[i]->paint(this);
    }

    QPainter p(this);
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
            Rect *r = new Rect;
            r->color = "blue";
            r->name = "my_rect";
            r->x = e->x();
            r->y = e->y();
            r->w = 100;
            r->h = 100;
            r->angle = 0;
            figures.append(r);
            update();
        } else if (e->button() == Qt::RightButton) {
            Circle *c = new Circle;
            c->color = "red";
            c->name = "my_circle";
            c->d = 25;
            c->x = e->x() - c->d/2;
            c->y = e->y() - c->d/2;
            c->angle = 0;
            figures.append(c);
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
        for (int i = 0; i < figures.size(); ++i) {
            QRect r = figures[i]->rect();
            if (e->x() >= r.x() && e->x() <= r.right() && e->y() >= r.y() && e->y() <= r.bottom()
                    && !selectedFigures.contains(figures[i])) {
                selectedFigures.append(figures[i]);
            }
        }
        update();
    } else if (e->button() == Qt::RightButton) {
    }
}

void PaintWidget::mouseMoveEvent(QMouseEvent *e)
{
    QPoint dP = e->pos() - oldPos;
    if (e->modifiers() & Qt::AltModifier) {
        if (selectedFigures.size() == 1) {
            QLineF l(0, 0, dP.x(), dP.y());
            selectedFigures[0]->angle = -l.angle();
            update();
        }
    } else {
        for (int i = 0; i < selectedFigures.size(); ++i) {
            selectedFigures[i]->x += dP.x();
            selectedFigures[i]->y += dP.y();
        }
        update();
        oldPos = e->pos();
    }
}

