#include <iostream>
#include <fstream>
#include <functional>
#include <cmath>
#include <limits>
#include <random>
#include <vector>
#include <algorithm>

// некоторые константы
const double eps = 0.001; // заданная точность

// особь
struct point
{
    double x;
    double y;

    point(double x_, double y_) : x(x_), y(y_) {}
    point() {}
};

// тип фитнесс-функции
// (возвращает double, принимает два аргумента типа double)
typedef std::function<double (point)> my_function;

/// набор фитнесс-функций
double func1(point p)
{
    return 17*std::pow(p.x-1,2)+0.3*std::pow(p.y+6,2);
}

double func2(point p)
{
    return 2*std::pow(p.x,2)+0.5*std::pow(p.y,2);
}

double func3(point p)
{
    return -10 * std::sin(5*std::pow(p.x,2)+M_PI*std::pow(p.y,2))
            /(5*std::pow(p.x,2)+M_PI*std::pow(p.y,2));
}

double length(point p)
{
    return std::sqrt(p.x * p.x + p.y * p.y);
}


/// методы популяций

// сортировка популяции в соответствии со значением фитнесс функции по убыванию
void sort_population(my_function f, std::vector<point> &population)
{
    // лямбда функция (увы, но без неё тут никак)
    // в квадратных скобках перечисляются переменные,
    // которые доступны внутри функции, в остальном это обычная такая функция.
    auto populator = [f](point a, point b) {
        return f(a) < f(b);
    };
    std::sort(population.begin(), population.end(), populator);
}

// скрещивание двух особей
point make_love(point mother, point father)
{
    point child((mother.x + father.x) / 2, (mother.y + father.y) / 2);
    return child;
}

// сам генетический алгоритм
// int ps = 50; // размер популяции
// int mf = 2; // частота мутаций
point genetic_algor(std::vector<double> &distances, my_function f, point minP,
                    point maxP, point g, int ps = 50, int mf = 5)
{


    std::random_device gen;
    std::uniform_real_distribution<double> xgen(minP.x, maxP.x); // диапазон по x
    std::uniform_real_distribution<double> ygen(minP.y, maxP.y); // диапазон по y
    std::uniform_real_distribution<double> mutagen(-7, 8); // диапазон мутаций

    // случайным образом создаем исходную популяцию
    // и сортируем её по фитнесс-функции
    std::vector<point> population;
    for (int i = 0; i < 100; ++i) {
        point p(xgen(gen), ygen(gen));
        population.push_back(p);
    }
    sort_population(f, population);

    bool finish = false;
    int generation = 1;
    double lastBest = f(population[0]);
    do {

        // размножаем популяцию при помощи случайных связей
        int sz = population.size();
        for (int i = 0; i < ps; ++i) {
            int a = std::rand() % sz;
            int b = std::rand() % sz;
            point child = make_love(population[a], population[b]);
            // добавляем некоторым детям мутаций
            if (i % mf == 0) {
                child.x += mutagen(gen);
                child.y += mutagen(gen);
            }
            population.push_back(child);
        }
        // производим естественный отбор
        sort_population(f, population);
        population.resize(ps);
        ++generation;

        // каждые 100 поколений проверяем, достигли ли мы цели
        if (generation % 200 == 0) {
            double best = f(population[0]);
            double d = std::abs(lastBest - best);
            if (d < eps) {
                finish = true;
                break;
            } else
                lastBest = best;
        }

        point d = population[0];
        d.x -= g.x;
        d.y -= g.y;
        distances.push_back(length(d));
    } while (!finish);

    return population[0];
}

int main(int, char **)
{
    std::srand(time(nullptr));

    std::vector<double> d1, d2, d3;

    std::cout << "Минимум внутри" << std::endl;
    genetic_algor(d1, func1, point(-30, -30), point(60, 60), point(1, -6));
    genetic_algor(d2, func2, point(-30, -30), point(60, 60), point(0, 0));
    genetic_algor(d3, func3, point(-30, -30), point(60, 60), point(0, 0));

    std::ofstream out1("o1.csv");
    out1 << "i;"
         << "17*(x-1)^2+0.3*(y+6)^2;"
         << "2*x^2+0.5*y^2;"
         << "-10 * std::sin(5*x^2+pi*y^2/(5*x^2+pi*y^2)"
         << std::endl;

    for (int i = 0; i < 50; ++i) {
        out1 << i << ";" << d1[i] << ";" << d2[i] << ";" << d3[i] << std::endl;
    }

    std::cout << "Минимум снаружи" << std::endl;
    d1.clear();d2.clear();d3.clear();
    genetic_algor(d1, func1, point(15, 15), point(55, 55), point(1, -6));
    genetic_algor(d2, func2, point(15, 15), point(55, 55), point(0, 0));
    genetic_algor(d3, func3, point(15, 15), point(55, 55), point(0, 0));

    std::ofstream out2("o2.csv");
    out2 << "i;"
         << "17*(x-1)^2+0.3*(y+6)^2;"
         << "2*x^2+0.5*y^2;"
         << "-10 * std::sin(5*x^2+pi*y^2/(5*x^2+pi*y^2)"
         << std::endl;

    for (int i = 0; i < 100; ++i) {
        out2 << i << ";" << d1[i] << ";" << d2[i] << ";" << d3[i] << std::endl;
    }

    std::cout << "минимум изнутри больше популяция" << std::endl;
    d1.clear();d2.clear();d3.clear();
    genetic_algor(d1, func1, point(-30, -30), point(60, 60), point(1, -6), 100);
    genetic_algor(d2, func2, point(-30, -30), point(60, 60), point(0, 0), 100);
    genetic_algor(d3, func3, point(-30, -30), point(60, 60), point(0, 0), 100);

    std::ofstream out3("o3.csv");
    out3 << "i;"
         << "17*(x-1)^2+0.3*(y+6)^2;"
         << "2*x^2+0.5*y^2;"
         << "-10 * std::sin(5*x^2+pi*y^2/(5*x^2+pi*y^2)"
         << std::endl;

    for (int i = 0; i < 100; ++i) {
        out3 << i << ";" << d1[i] << ";" << d2[i] << ";" << d3[i] << std::endl;
    }

    std::cout << "Минимум снаружи, больше популяция" << std::endl;
    d1.clear();d2.clear();d3.clear();
    genetic_algor(d1, func1, point(15, 15), point(55, 55), point(1, -6), 100);
    genetic_algor(d2, func2, point(15, 15), point(55, 55), point(0, 0), 100);
    genetic_algor(d3, func3, point(15, 15), point(55, 55), point(0, 0), 100);

    std::ofstream out4("o4.csv");
    out4 << "i;"
         << "17*(x-1)^2+0.3*(y+6)^2;"
         << "2*x^2+0.5*y^2;"
         << "-10 * std::sin(5*x^2+pi*y^2/(5*x^2+pi*y^2)"
         << std::endl;

    for (int i = 0; i < 100; ++i) {
        out4 << i << ";" << d1[i] << ";" << d2[i] << ";" << d3[i] << std::endl;
    }

    std::cout << "Минимум снаружи, больше мутаций" << std::endl;
    d1.clear();d2.clear();d3.clear();
    genetic_algor(d1, func1, point(15, 15), point(55, 55), point(1, -6), 100, 2);
    genetic_algor(d2, func2, point(15, 15), point(55, 55), point(0, 0), 100, 2);
    genetic_algor(d3, func3, point(15, 15), point(55, 55), point(0, 0), 100, 2);

    std::ofstream out5("o5.csv");
    out5 << "i;"
         << "17*(x-1)^2+0.3*(y+6)^2;"
         << "2*x^2+0.5*y^2;"
         << "-10 * std::sin(5*x^2+pi*y^2/(5*x^2+pi*y^2)"
         << std::endl;

    for (int i = 0; i < 100; ++i) {
        out5 << i << ";" << d1[i] << ";" << d2[i] << ";" << d3[i] << std::endl;
    }
}
