#include <QApplication>
#include <QDir>
#include "mainwindow.h"
#include "container.h"

int main(int argc, char **argv) {
    QString dd = QDir::home().absoluteFilePath("Figures/test.txt");
    QDir dr;
    dr.mkpath(dr.absolutePath());
    Container f;
    f.addFigure(new Circle("b", "black", 35));
    f.addFigure(new Triangle("t", "magenta", QPoint(), QPoint()));
    f.addFigure(new Rect("rar", "red", 100, 25));
    f.figureAt(2)->setPos(QPoint(15, 35));
    f.figureAt(0)->setRotation(45);
    f.save(dd);

    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    return app.exec();
}
