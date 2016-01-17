#include "container.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>

Container::Container()
{

}

Container::~Container()
{
    qDeleteAll(figures);
}

void Container::addFigure(Figure *figure)
{
    figures.append(figure);
}

void Container::removeFigure(Figure *figure)
{
    figures.removeAll(figure);
}

Figure *Container::figureAt(int i) const
{
    return figures.at(i);
}

int Container::figuresCount() const
{
    return figures.count();
}

void Container::save(const QString &fileName)
{
    QFile file(fileName);
    file.open(QFile::WriteOnly|QFile::Text);
    QTextStream out(&file);

    for (int i = 0; i < figures.size(); ++i) {
        out << figures[i]->save().join(' ') << "\n";
    }
}

void Container::load(const QString &fileName)
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
            f->load(strs);
            figures.append(f);
        }
    }
}
