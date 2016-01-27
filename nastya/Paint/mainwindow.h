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
    int Tra();
    void Trol();

    QPaintWidget *wgtt();
protected:
    void changeEvent(QEvent *e);

private:
    int traa = 117;
    int trabl = 117;
    Ui::MainWindow *ui;
    QPaintWidget *wgt;

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *);
};

#endif // MAINWINDOW_H
