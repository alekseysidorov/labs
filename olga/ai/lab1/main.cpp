#include <iostream>
#include <fstream>
#include <functional>
#include <cmath>
#include <limits>
#include <random>
#include <vector>

// некоторые константы
const double h = 0.000000001; // приращение аргумента

// тип исследуемой функции (возвращает double, принимает два аргумента типа double)
typedef std::function<double (double x, double y)> my_function;

/// набор исследуемых функий
double func1(double x, double y)
{
    return 0.5*std::pow(x,2)+0.9*std::pow(y-7, 2);
}

double func2(double x, double y)
{
    return 17*std::pow(x-1,2)+0.3*std::pow(y+6,2);
}

double func3(double x, double y)
{
    return 2*std::pow(x,2)+0.5*std::pow(y,2);
}

double func4(double x, double y)
{
    return -10 * std::sin(5*std::pow(x,2)+M_PI*std::pow(y,2))/(5*std::pow(x,2)+M_PI*std::pow(y,2));
}

struct point
{
    double x;
    double y;

    point(double x_, double y_) : x(x_), y(y_) {}
    point() {}
};

struct result {
    point p; // конечная точка
    std::vector<double> steps; // итерации
};

/// метод градиентного спуска

// програмно считаем производную по x
double d_x(my_function f, double x, double y)
{
    return (f(x + h, y) - f(x, y)) / h;
}

// програмно считаем производную по y
double d_y(my_function f, double x, double y)
{
    return (f(x, y + h) - f(x, y)) / h;
}

double length(double x, double y)
{
    return std::sqrt(x * x + y * y);
}

// простой градиентный спуск
result gradient(my_function f, point p, point to, int iters, double d)
{
    result r;

    for (int i = 0; i < iters; ++i) {
        double dx = d_x(f, p.x, p.y);
        double dy = d_y(f, p.x, p.y);
        double l = length(dx, dy);

        // координаты следующей точки
        p.x -= d * (dx / l);
        p.y -= d * (dy / l);

        // расстояние до минимума
        double dt = length(p.x - to.x, p.y - to.y);
        r.steps.push_back(dt);
    }
    std::cout << "f("  << p.x << ", " << p.y << ") = " << f(p.x, p.y) << std::endl;
    r.p = p;
    return r;
}

/// метод имитации отжига

// распределение Бокса-Мюллера
double generateGaussianNoise(double mu, double sigma)
{
    const double epsilon = std::numeric_limits<double>::min();
    const double two_pi = 2.0 * M_PI;
    double u1, u2;

    static double z0, z1;
    static bool generate;
    generate = !generate;
    if (!generate) {
        return z1 * sigma + mu;
    }
    do {
        u1 = std::rand() / double(RAND_MAX);
        u2 = std::rand() / double(RAND_MAX);
    } while (u1 <= epsilon);
    z0 = std::sqrt(-2.0 * log(u1)) * cos(two_pi * u2);
    z1 = std::sqrt(-2.0 * log(u1)) * sin(two_pi * u2);
    return z0 * sigma + mu;
}

/// вероятность перехода
double h_prob(double dE, double T)
{
    double r = 1.0 / (1.0 + std::exp(dE / T));
    return r;
}

/// уменьшение температуры
double dec_temperature(double T, int iter)
{
    return T / (1.0 + iter);
}

/// значение энергии
double delta_energy(my_function f, point a, point b)
{
    double r1 = f(b.x, b.y);
    double r2 = f(a.x, a.y);
    return r2 - r1;
}

// метод имитации отжига
result annealing(my_function f, point p, point to, int iters, double T_0)
{
    result r;
    // генератор случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());

    double T = T_0;
    for (int i = 0; i < iters; ++i) {

        point n_p(0, 0);
        n_p.x = generateGaussianNoise(p.x, std::sqrt(T));
        n_p.y = generateGaussianNoise(p.y, std::sqrt(T));
        double de = delta_energy(f, n_p, p);

        // новое значение энергии лучше
        if (de < 0) {
            p = n_p;
        } else {
            double probality = h_prob(de, T);
            double v = double(rand()) / double(RAND_MAX);
            if (v <= probality) {
                p = n_p;
            }
        }
        T = dec_temperature(T_0, i);

        // вычисляем расстояние до истинного минимума
        double dx = std::abs(p.x - to.x);
        double dy = std::abs(p.y - to.y);
        double l = length(dx, dy);

        r.steps.push_back(l);
    }
    std::cout << "f("  << p.x << ", " << p.y << ") = " << r.steps.back() << std::endl;
    r.p = p;
    return r;
}

int main(int, char **)
{
    std::srand(time(nullptr));

    point po(24, 32);

    int its = 600; //количество итераций (намерено ограничиваем так, чтобы график получился наглядным)
    std::cout << "g1" << std::endl;

    { // вложеный блок, чтобы не ошибиться случайно
        result r1 = gradient(func1, po, point(0, 7), its, 0.1);
        result r2 = gradient(func2, po, point(1, -6), its, 0.1);
        result r3 = gradient(func3, po, point(0, 0), its, 0.1);

        std::ofstream out("g1.csv");
        out << "i;f1;f2;f3" << std::endl;
        for (int i = 0; i < its; ++i) {
            out << i << ";"
                << r1.steps[i] << ";"
                << r2.steps[i] << ";"
                << r3.steps[i] << std::endl;

        }
    }

    std::cout << "g2" << std::endl;
    { // вложеный блок, чтобы не ошибиться случайно
        result r1 = gradient(func4, point(0.5, 0.5), point(0, 0), its, 0.001);
        result r2 = gradient(func4, point(3, 3), point(0, 0), its, 0.001);

        std::ofstream out("g2.csv");
        out << "i;(0.5, 0.5);(3, 3);" << std::endl;
        for (int i = 0; i < its; ++i) {
            out << i << ";"
                << r1.steps[i] << ";"
                << r2.steps[i] << std::endl;

        }
    }

    std::cout << "a1" << std::endl;
    { // вложеный блок, чтобы не ошибиться случайно
        result r1 = annealing(func1, po, point(0, 7), its, 50);
        result r2 = annealing(func2, po, point(1, -6), its, 50);
        result r3 = annealing(func3, po, point(0, 0), its, 50);

        std::ofstream out("a1.csv");
        out << "i;f1;f2;f3" << std::endl;
        for (int i = 0; i < its; ++i) {
            out << i << ";"
                << r1.steps[i] << ";"
                << r2.steps[i] << ";"
                << r3.steps[i] << std::endl;

        }
    }

    std::cout << "a2" << std::endl;
    { // вложеный блок, чтобы не ошибиться случайно
        result r1 = annealing(func1, po, point(0, 7), its, 200);
        result r2 = annealing(func2, po, point(1, -6), its, 200);
        result r3 = annealing(func3, po, point(0, 0), its, 200);

        std::ofstream out("a2.csv");
        out << "i;f1;f2;f3" << std::endl;
        for (int i = 0; i < its; ++i) {
            out << i << ";"
                << r1.steps[i] << ";"
                << r2.steps[i] << ";"
                << r3.steps[i] << std::endl;

        }
    }

    std::cout << "a3" << std::endl;
    its = 600;
    { // вложеный блок, чтобы не ошибиться случайно
        result r1 = annealing(func4, point(1, 1), point(0, 0), its, 0.5);
        result r2 = annealing(func4, point(1, 1), point(0, 0), its, 5);
        result r3 = annealing(func4, point(1, 1), point(0, 0), its, 50);

        std::ofstream out("a3.csv");
        out << "i;T=0.5;T=5;T=50" << std::endl;
        for (int i = 0; i < its; ++i) {
            out << i << ";"
                << r1.steps[i] << ";"
                << r2.steps[i] << ";"
                << r3.steps[i] << std::endl;

        }
    }
}
