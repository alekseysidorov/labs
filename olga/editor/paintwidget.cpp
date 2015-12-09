#include "paintwidget.h"
#include "figures.h"

#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDebug>

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
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

void PaintWidget::paintEvent(QPaintEvent *)
{
    for (int i = 0; i < figures.size(); ++i) {
        figures[i]->paint(this);
    }
}

