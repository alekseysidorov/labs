#include <iostream>
#include <vector>
#include <ctime>
#include <cassert>

void sort_bubble(std::vector<int> &v)
{
    for (size_t i = 0; i < v.size() - 1; ++i) {
        for (size_t j = 0; j < v.size() - i - 1; j++)
            if (v[j] > v[j +1])
                std::swap(v[j], v[j+1]);
    }
}

std::vector<int> merge(std::vector<int> &c, const std::vector<int> &a, const std::vector<int> &b)
{
    size_t j = 0, k = 0, i = 0;

    while (j < a.size() && k < b.size()) {
        if (a[j] < b[k]) {
            c[i] = a[j];
            ++j;
        } else {
            c[i] = b[k];
            ++k;
        }
        ++i;
    }

    for (; j < a.size(); ++j, ++i)
        c[i] = a[j];
    for (; k < b.size(); ++k, ++i)
        c[i] = b[k];

    return c;
}

std::vector<int> sort_merge(std::vector<int> &v)
{
    if (v.size() == 1)
        return v;

    size_t m = v.size() / 2;

    std::vector<int> left(v.begin(), v.begin() + m);
    std::vector<int> right(v.begin() + m, v.end());

    left = sort_merge(left);
    right = sort_merge(right);

    return merge(v, left, right);
}

int main()
{
    std::vector<int> v, v1;
    v.resize(100000);

    for (size_t i = 0; i < v.size(); ++i)
        v[i] = std::rand();

    std::cout << "Количество элементов: " << v.size() << std::endl;

    v1 = v;

    std::clock_t c = clock();
    sort_bubble(v);
    std::cout << "Пузырек - время работы: " << (clock() - c) / 1e6 << " секунд" << std::endl;

    c = clock();
    v1 = sort_merge(v1);
    std::cout << "Слияние - время работы: " << (clock() - c) / 1e6 << " секунд" << std::endl;

    assert(v == v1);

    return 0;
}

