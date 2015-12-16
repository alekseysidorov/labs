#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>
#include <QPainter>
#include <QThread>

class Generator : public QThread
{
    Q_OBJECT
public:
    Generator();

    bool paused;
    QSize size;
protected:
    void run();
    void draw();
signals:
    void painted(const QImage &image);
};

#endif // GENERATOR_H
