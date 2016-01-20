#include "mainwindow.h"
#include <QApplication>
#include "thread.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Thread tre(w.wgt);
    tre.start();
    Circle hh(78, 77, 200, "blue", "wwj");
    hh.paint(w.wgt);
    Rectanglee l(130, 0, 50, 160, "blue", "ll");
    l.paint(w.wgt);
    w.show();
    return a.exec();
}
