#include "generator.h"

#include <QMutex>
#include <QPixmap>
#include <QImage>

Generator::Generator() : paused(true), size(1000, 1000)
{

}

void Generator::run()
{
    while (1) {
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
