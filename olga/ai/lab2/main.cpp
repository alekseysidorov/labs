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

// тип фитнесс-функции (возвращает double, принимает два аргумента типа double)
typedef std::function<double (point)> my_function;

/// набор фитнесс-функций
double func1(point p)
{
    double r = 0.8 * std::pow(p.x, 2) + 0.5 * std::pow((p.y - 1), 2);
    return r;
}

double func2(point p)
{
    return p.x * p.x + p.y * p.y;
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
    // в квадратных скобках перечисляются переменные, которые доступны внутри функции, в остальном это обычная такая функция.
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
point genetic_algor(std::string file, my_function f, point minP, point maxP)
{
    std::random_device gen;
    std::uniform_real_distribution<double> xgen(minP.x, maxP.x); // диапазон по x
    std::uniform_real_distribution<double> ygen(minP.y, maxP.y); // диапазон по y
    std::uniform_real_distribution<double> mutagen(-7, 8); // диапазон мутаций

    // случайным образом создаем исходную популяцию и сортируем её по фитнесс-функции
    std::vector<point> population;
    for (int i = 0; i < 200; ++i) {
        point p(xgen(gen), ygen(gen));
        population.push_back(p);
    }
    sort_population(f, population);

    std::ofstream out(file);
    out << "i;x;y;l" << std::endl;

    bool finish = false;
    int generation = 1;
    double lastBest = f(population[0]);
    do {

        // размножаем популяцию при помощи случайных связей
        int sz = population.size();
        for (int i = 0; i < 100; ++i) {
            int a = std::rand() % sz;
            int b = std::rand() % sz;
            point child = make_love(population[a], population[b]);
            // добавляем некоторым детям мутаций
            if (i % 4 == 0) {
                child.x += mutagen(gen);
                child.y += mutagen(gen);
            }
            population.push_back(child);
        }
        // производим естественный отбор
        sort_population(f, population);
        population.resize(50);
        ++generation;

        std::cout << population[0].x << " " << population[0].y << " " << f(population[0]) << std::endl;

        // каждые 50 поколений проверяем, достигли ли мы цели
        if (generation % 50 == 0) {
            double best = f(population[0]);
            double d = std::abs(lastBest - best);
            if (d < eps) {
                finish = true;
                break;
            } else
                lastBest = best;
        }
    } while (!finish);

    return population[0];
}

int main(int, char **)
{
    std::srand(time(nullptr));

    std::cout << "gradient" << std::endl;
    std::cout << "func1" << std::endl;
    genetic_algor("funct1.csv", func1, point(-30, -30), point(60, 60));
    std::cout << "func2" << std::endl;
    genetic_algor("funct2.csv", func2, point(30, 30), point(60, 60));
}
