#include <iostream>
#include <fstream>
#include <functional>
#include <cmath>
#include <limits>

// некоторые константы
const double eps = 0.001; // заданная точность
const double h = 0.000001; // приращение аргумента

// тип исследуемой функции (возвращает double, принимает два аргумента типа double)
typedef std::function<double (double x, double y)> my_function;

/// набор исследуемых функий
double func1(double x, double y)
{
    return 0.8 * std::pow(x, 2) + 0.5 * std::pow((y - 1), 2);
}

double func2(double x, double y)
{
    return x * x + y * y;
}

struct point
{
    double x;
    double y;

    point(double x_, double y_) : x(x_), y(y_) {}
};

/// метод градиентного спуска

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

double length(double x, double y)
{
    return std::sqrt(x * x + y * y);
}

// простой градиентный спуск
point gradient(std::string file, my_function f, point p, point to, int iters, double d)
{
    std::ofstream out(file);
    out << "i;x;y;l" << std::endl;
    point p0 = p;
    double fp0 = f(p0.x, p0.y);
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

        out << i << ";" << p.x << ";" << p.y << ";" << l << std::endl;

        // вычисляем дельту между предыдущим и этим шагом и выходим если она становится меньше eps
        double fp = f(p.x, p.y);
        l = std::abs(fp - fp0);
        if (l < eps) {
            break;
        }
        p0 = p;
        fp0 = fp;
    }
    return p;
}

/// метод имитации отжига

/// функция распределения g
double g_dist(double x1, double x2, double T)
{
    double D = 2; // размерность пространства
    double r = std::pow(2 * M_PI * T, -D / 2) * std::exp(-std::pow(x2 - x1, 2) / (2 * T));
    return r;
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
double get_energy(my_function f, point a, point b)
{
    return std::abs(f(b.x, b.y) - f(a.x, a.y));
}

/// распределение Бокса-Мюллера (взято с просторов интернета)
double generateGaussianNoise(double mu, double sigma)
{
    const double epsilon = std::numeric_limits<double>::min();
    const double two_pi = 2.0 * M_PI;
    double u1, u2;
    static double z0, z1;
    static bool generate;
    generate = !generate;
    if (!generate)
    {
        return z1 * sigma + mu;
    }
    do
    {
        u1 = std::rand() / double(RAND_MAX);
        u2 = std::rand() / double(RAND_MAX);
    } while (u1 <= epsilon);
    z0 = std::sqrt(-2.0 * std::log(u1)) * std::cos(two_pi * u2);
    z1 = std::sqrt(-2.0 * std::log(u1)) * std::sin(two_pi * u2);
    return z0 * sigma + mu;
}

// метод имитации отжига
point annealing(std::string file, my_function f, point p, point to, int iters, double T_0)
{
    std::ofstream out(file);
    out << "i;x;y;l" << std::endl;

    double e = get_energy(f, to, p);
    double T = T_0;
    for (int i = 0; i < iters; ++i) {
        point n_p(0, 0);
        n_p.x = generateGaussianNoise(p.x, std::sqrt(T));
        n_p.y = generateGaussianNoise(p.y, std::sqrt(T));

        double n_e = get_energy(f, to, n_p);

        // новое значение энергии лучше
        if (n_e < e) {
            p = n_p;
            e = n_e;
        } else {
            double probality = h_prob(n_e - e, T);
            double v = double(rand()) / double(RAND_MAX);
            if (v <= probality) {
                p = n_p;
                e = n_e;
            }
        }
        T = dec_temperature(T_0, i);
    }
    return p;
}

int main(int, char **)
{
    std::srand(time(nullptr));

    std::cout << "gradient" << std::endl;
    std::cout << "func1" << std::endl;
    gradient("funct1.csv", func1, point(32, 45), point(0, 1), 10000, 0.01);
    std::cout << "func2" << std::endl;
    gradient("funct2.csv", func2, point(32, 45), point(0, 0), 10000, 0.01);

    std::cout << "annealing" << std::endl;
    annealing("funct1.csv", func1, point(32, 45), point(0, 1), 10000000, 1000000);
}
