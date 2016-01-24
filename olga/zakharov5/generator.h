#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>
#include <QPainter>
#include <QThread>

class Generator : public QThread
{
    Q_OBJECT

    bool paused = true;
    bool finished = false;
    QSize size;
public:
    Generator();
    ~Generator();

    void setPaused(bool set);
    void finish();
protected:
    void run();
    void draw();
signals:
    void painted(const QImage &image);
};

#endif // GENERATOR_H
