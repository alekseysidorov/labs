#include <iostream>
#include <functional>
#include <cmath>

// некоторые константы
const double eps = 0.001; // заданная точность
const double h = 0.000001; // приращение аргумента

// тип исследуемой функции (возвращает double, принимает два аргумента типа double)
typedef double (*my_function)(double x, double y); // немного наркоманский синтаксис

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
    double a1 = f(x, y + h * 0.5);
    double a2 = f(x, y - h * 0.5);
    return (a2 - a1) / h;
}

struct point
{
    double x;
    double y;
};

// простой градиентный спуск
point gradient1(my_function, double x, double y)
{

}

// набор исследуемых функий
double func1(double x, double y)
{
    return 0.8 * std::pow(x, 2) + 0.5 * std::pow((y - 1), 2);
}

int main(int, char **)
{
    double dx = d_x(func1, 1, 0);
    double dy = d_y(func1, 0, 2);

    std::cout << dx << " " << dy << std::endl;
}
