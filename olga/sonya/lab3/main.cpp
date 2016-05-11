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
    return x * x + 20 * (y *y + std::sin(x));
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

// просто длина вектора
double length(double x, double y)
{
    return std::sqrt(x * x + y * y);
}

// покоординатный спуск по оси x
int down_x(double &x, double &y, double e)
{
    double d = 0.1;

    int i = 0;
    double df = std::abs(f(x + d, y) - f(x, y));
    while (df > e) {
        if (f(x, y) > f(x + d, y))
            x -= d;
        else
            x += d;

        df = std::abs(f(x, y) - f(x - d, y));
        ++i;
    }
    return i;
}

// покоординатный спуск по оси y
int down_y(double &x, double &y, double e)
{
    double d = 0.1;

    int i = 0;
    double df = std::abs(f(x, y + d) - f(x, y));
    while (df > e) {
        if (f(x, y) > f(x, y + d))
            y += d;
        else
            y -= d;

        df = std::abs(f(x, y) - f(x, y - d));
        ++i;
    }
    return i;
}

// покоординатный спуск по обеим осям

void down(std::string name, double x, double y, double e)
{
    std::cout << "  down x0=" << x << " y=" << y << " e=" << e << std::endl;

    double x0 = x; // запоминаем исходный x

    std::ofstream out(name + "_down.csv");
    int ix = down_x(x, y, e);
    int iy = down_y(x0, y, e);
    out << ix << ";" << iy << ";" << x << ";" << y << ";" << f(x, y) << ";" << std::endl;
    out.close();

    std::cout << "    finished x=" << x << ", y=" << y << " f(x,y)=" << f(x, y) << std::endl;
}

// простой градиентный спуск с шагом d
void simple_gradient(std::string name, double x, double y, double e, double d)
{
    std::cout << "  simple gradient x0=" << x << " y=" << y << " e=" << e << std::endl;

    std::ofstream out(name + "_simple_gradient.csv");

    while (1) {
        double dx = d_x(x, y);
        double dy = d_y(x, y);
        double l = length(dx, dy);

        // проверяем, что изменение градиента больше погрешности
        if (l < e)
            break;

        // изменения для перехода в следующую точку
        dx = d * (dx / l);
        dy = d * (dy / l);

        // переходим в следующую точку
        x -= dx;
        y -= dy;
        out << x << ";" << y << std::endl;
    }
    std::cout << "    finished x=" << x << ", y=" << y << " f(x,y)=" << f(x, y) << std::endl;
}

// градиентный спуск с дроблением шага
void drob_gradient(std::string name, double x, double y, double e, double d)
{
    std::cout << "  drob gradient x0=" << x << " y=" << y << " e=" << e << std::endl;

    std::ofstream out(name + "_simple_gradient.csv");

    while (1) {
        double dx = d_x(x, y);
        double dy = d_y(x, y);
        double l = length(dx, dy);

        // проверяем, что изменение градиента больше погрешности
        if (l < e)
            break;

        // изменения для перехода в следующую точку
        dx = d * (dx / l);
        dy = d * (dy / l);

        // проверяем, нужно ли изменить значение шага
        if (f(x - dx, y - dy) > f(x, y)) {
            d /= 2.0;
        }
        // переходим в следующую точку
        x -= dx;
        y -= dy;
        out << x << ";" << y << std::endl;
    }
    std::cout << "    finished x=" << x << ", y=" << y << " f(x,y)=" << f(x, y) << std::endl;
}

// градиентный спуск с заранее заданным шагом
void step_gradient(std::string name, double x, double y, double e)
{
    std::cout << "  step gradient x0=" << x << " y=" << y << " e=" << e << std::endl;

    std::ofstream out(name + "_simple_gradient.csv");

    int k = 1;
    while (1) {
        double d = 1.0 / k; ++k; //изменяем размер шага

        double dx = d_x(x, y);
        double dy = d_y(x, y);
        double l = length(dx, dy);

        // проверяем, что изменение градиента больше погрешности
        if (l < e)
            break;

        // изменения для перехода в следующую точку
        dx = d * (dx / l);
        dy = d * (dy / l);

        // переходим в следующую точку
        x -= dx;
        y -= dy;
        out << x << ";" << y << std::endl;
    }
    std::cout << "    finished x=" << x << ", y=" << y << " f(x,y)=" << f(x, y) << std::endl;
}

void make_lab(std::string name, double x, double y, double e)
{
    std::cout << "-> make_lab: " << name << std::endl;

    down(name, x, y, e);
    simple_gradient(name, x, y, e, 0.2);
    drob_gradient(name, x, y, e, 0.2);
    step_gradient(name, x, y, e);
}

int main(int, char **)
{
    std::cout << std::fixed;

    double x0 = 0.9; double y0 = 0.7;

    make_lab("epsilon-0.9", x0, y0, 0.9);
    make_lab("epsilon-0.07", x0, y0, 0.07);
    make_lab("epsilon-0.6", x0, y0, 0.6);

//    simple_gradient(-3, 2, 0.5, 0.2);
//    simple_gradient(-3, 2, 0.02, 0.01);
//    //drob_gradient()

//    step_gradient(-3, 2, 0.2);
}
