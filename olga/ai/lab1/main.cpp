#include <iostream>
#include <functional>
#include <cmath>

// некоторые константы
const double eps = 0.1; // заданная точность
const double h = 0.000001; // приращение аргумента

// тип исследуемой функции (возвращает double, принимает два аргумента типа double)
typedef std::function<double (double x, double y)> my_function;

// програмно считаем производную по x
double d_x(my_function f, double x, double y)
{
    double a1 = f(x - h * 0.5, y);
    double a2 = f(x + h * 0.5, y);
    return (a2 - a1) / h;
}

// програмно считаем производную по y
double d_y(my_function f, double x, double y)
{
    double a1 = f(x, y - h * 0.5);
    double a2 = f(x, y + h * 0.5);
    return (a2 - a1) / h;
}

struct point
{
    double x;
    double y;

    point(double x_, double y_) : x(x_), y(y_) {}
};

double length(double x, double y)
{
    return std::sqrt(x * x + y * y);
}

// простой градиентный спуск
point gradient1(my_function f, point p, point to, int iters, double d)
{
    point p0 = p;
    for (int i = 0; i < iters; ++i) {
        double dx = d_x(f, p.x, p.y);
        double dy = d_y(f, p.x, p.y);
        double n = length(p.x, p.y);

        p.x -= d * (dx / n);
        p.y -= d * (dy / n);

        // вычисляем расстояние до истинного минимума
        dx = std::abs(p.x - to.x);
        dy = std::abs(p.y - to.y);
        double l = length(dx, dy);

        std::cout << i << ";" << p.x << ";" << p.y << ";" << l << std::endl;

        // вычисляем дельту между предыдущим и этим шагом и выходим если она становится меньше eps
        dx = std::abs(p.x - p0.x);
        dy = std::abs(p.y - p0.y);
        if (length(dx, dy) < eps * d) {
            break;
        }
        p0 = p;
    }
    return p;
}

// набор исследуемых функий
double func1(double x, double y)
{
    return 0.8 * std::pow(x, 2) + 0.5 * std::pow((y - 1), 2);
}

int main(int, char **)
{
    point p = gradient1(func1, point(27, 31), point(0, 1), 10000, 0.1);
}
