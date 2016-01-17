#ifndef CONTAINER_H
#define CONTAINER_H
#include "figures.h"

class Container
{
    QList<Figure*> figures;
public:
    Container();
    ~Container();

    void addFigure(Figure *figure);
    void removeFigure(Figure *figure);
    Figure *figureAt(int i) const;
    int figuresCount() const;

    void load(const QString &fileName);
    void save(const QString &dir);
};


#endif // CONTAINER_H
