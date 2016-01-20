#include "mainwindow.h"
#include <QApplication>
#include "thread.h"
#include "figlibrary.h"

int main(int argc, char *argv[])
{
    QDir fi = QDir::home();
    FigLibrary lib;
    Circle *hh = new Circle(78, 77, 200, "blue", "wwj");
    lib.add(hh);
    Rectanglee *l = new Rectanglee(130, 0, 50, 160, "yellow", "ll");
    lib.add(l);
    lib.save(fi.absoluteFilePath("Figures/"));
    l->rotat(13);
    l->moveto(140, 35);

    QApplication a(argc, argv);
    MainWindow w;
    Thread tre(w.wgtt());
    tre.start();
    w.download();
    w.show();
    return a.exec();
}
