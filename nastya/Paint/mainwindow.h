#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//nash class
#include "qpaintwidget.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void clear();
    void save();
    void gener();
    void download();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
public:
    // Указатель на объект нашего класса
    QPaintWidget *wgt;
};

#endif // MAINWINDOW_H
