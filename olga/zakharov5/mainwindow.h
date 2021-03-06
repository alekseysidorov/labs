#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "generator.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class PaintWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void start();
    void save();
private:
    Ui::MainWindow *ui;
    PaintWidget *wgt;
    Generator *generator;
protected:
    void keyPressEvent(QKeyEvent *);
};

#endif // MAINWINDOW_H
