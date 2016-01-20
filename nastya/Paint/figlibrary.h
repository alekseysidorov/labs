#ifndef FIGLIBRARY_H
#define FIGLIBRARY_H
#include "figures.h"

class FigLibrary
{
    QList<Figure*> figs;
public:
    FigLibrary();

    void add(Figure *fi);
    void remove(int i);
    QList<Figure*> figss();

    void load(QString pp);
    void save(QString ss);
    void clear();
};

#endif // FIGLIBRARY_H
