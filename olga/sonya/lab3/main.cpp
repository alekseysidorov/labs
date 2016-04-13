#include <iostream>
#include <fstream>
#include <functional>
#include <cmath>
#include <limits>
#include <random>
#include <vector>

// некоторые константы
const double h = 0.000000001; // приращение аргумента

double f(double x, double y)
{
    return (5 * std::atan(std::pow((x + 3), 2)) + std::pow(x, 2) + std::atan(std::pow((2 * y - 1), 2)));
}

/// метод градиентного спуска

// програмно считаем производную по x
double d_x(double x, double y)
{
    return (f(x + h, y) - f(x, y)) / h;
}

// програмно считаем производную по y
double d_y(double x, double y)
{
    return (f(x, y + h) - f(x, y)) / h;
}

double length(double x, double y)
{
    return std::sqrt(x * x + y * y);
}

// простой градиентный спуск с шагом d
void simple_gradient(double x, double y, double e, double d)
{
    std::cout << "simple gradient x0=" << x << " y=" << y << " e=" << e << std::endl;

    while (1) {
        double dx = d_x(x, y);
        double dy = d_y(x, y);
        double l = length(dx, dy);

        // изменения для перехода в следующую точку
        dx = d * (dx / l);
        dy = d * (dy / l);
        // если они слишком малы, то выходим
        if (std::max(std::abs(dx), std::abs(dy)) < e)
            break;

        // переходим в следующую точку
        x -= dx;
        y -= dy;
        std::cout << x << ";" << y << std::endl;
    }
    std::cout << "finished x=" << x << ", y=" << y << std::endl;
}

// градиентный спуск с дроблением шага
void drob_gradient(double x, double y, double e, double d)
{
    std::cout << "simple gradient x0=" << x << " y=" << y << " e=" << e << std::endl;

    while (1) {
        double dx = d_x(x, y);
        double dy = d_y(x, y);

        // координаты следующей точки
        double l = length(dx, dy);
        dx = d * (dx / l);
        dy = d * (dy / l);

        // смотрим изменение координаты
        if (length(dx, dy) < e)
            break;

        // переходим в следующую точку
        x -= dx;
        y -= dy;
        std::cout << x << ";" << y << std::endl;
    }
    std::cout << "finished x=" << x << ", y=" << y << std::endl;
}

// градиентный спуск с заранее заданным шагом
void step_gradient(double x, double y, double e)
{
    std::cout << "simple gradient x0=" << x << " y=" << y << " e=" << e << std::endl;

    int k = 1;
    while (1) {
        double d = 1.0 / k;
        double dx = d_x(x, y);
        double dy = d_y(x, y);

        // координаты следующей точки
        double l = length(dx, dy);
        dx = d * (dx / l);
        dy = d * (dy / l);

        // смотрим изменение координаты
        if (length(dx, dy) < e)
            break;

        // переходим в следующую точку
        x -= dx;
        y -= dy;
        std::cout << x << ";" << y << std::endl;

        // увеличиваем k
        ++k;
    }
    std::cout << "finished x=" << x << ", y=" << y << std::endl;
}


int main(int, char **)
{
    simple_gradient(-3, 2, 0.5, 0.2);
    simple_gradient(-3, 2, 0.02, 0.01);
    //drob_gradient()

    step_gradient(-3, 2, 0.2);
}
