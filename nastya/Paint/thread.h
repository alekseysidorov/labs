#ifndef THREAD_H
#define THREAD_H
#include <QThread>
#include "qpaintwidget.h"
#include "mainwindow.h"


class Thread :public QThread
{
    Q_OBJECT
public:
    Thread(QPaintWidget *wgtt, MainWindow *w1);
    QPaintWidget *wgt;
    ~Thread();

    // QThread interface
protected:
    void run();
signals:
    void mainn();
    void updatePaint();
private:
    MainWindow *w;
};

#endif // THREAD_H
