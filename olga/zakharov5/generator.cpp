#include "generator.h"

#include <QMutex>
#include <QPixmap>
#include <QImage>

Generator::Generator() : paused(true), size(1000, 1000)
{

}

Generator::~Generator()
{
    finish();
    quit();
    wait();
}

void Generator::setPaused(bool set)
{
    paused = set;
}

void Generator::finish()
{
    finished = true;
}

void Generator::run()
{
    while (!finished) {
        if (!paused) {
            draw();
        }
        msleep(1);
    }
}

void Generator::draw()
{
    QImage image(size, QImage::Format_RGB32);
    for (int i = 0; i < size.width(); i++) {
        for (int j = 0; j < size.height(); j++) {
            image.setPixel(i, j, qrand());
        }
    }
    painted(image);
}
