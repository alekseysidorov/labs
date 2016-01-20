#ifndef THREAD_H
#define THREAD_H
#include <QThread>
#include "qpaintwidget.h"


class Thread :public QThread
{
    Q_OBJECT
public:
    Thread(QPaintWidget *wgtt);
    QPaintWidget *wgt;

    // QThread interface
protected:
    void run();
signals:
    void updatePaint();
};

#endif // THREAD_H
