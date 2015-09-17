#include <vector>

#include <iostream>

#include <ctime>
#include <cassert>
#include <cstdlib>

template <typename Iterator>
void sort_bubble(Iterator begin, Iterator end)
{
    for (auto i = begin; i != end; ++i) {
        for (auto j = begin; (j - begin) != (end - i - 1); j++)
            if (*j > *(j+1))
                std::swap(*j, *(j+1));
    }
}

void sort_quick(std::vector<int> &v, const int begin, const int end)
{
    int i = begin;
    int j = end;
    const auto m = v[(begin + end + 1) / 2];

    do {
        while (v[i] < m) ++i;
        while (v[j] > m) --j;

        if (i <= j) {
            std::swap(v[i], v[j]);
            ++i; --j;
        }
    } while (i <= j);

    if (j > begin)
        sort_quick(v, begin, j);
    if (i < end)
        sort_quick(v, i, end);
}

template <typename Iterator>
void sort_quick_iterator(const Iterator begin, const Iterator end)
{
    const auto m = *(begin + (end - begin) / 2);

    auto i = begin, j = end - 1;

    do {
        while (*i < m) ++i;
        while (*j > m) --j;

        if (i <= j) {
            std::swap(*i, *j);
            ++i; --j;
        }

    } while (i <= j);

    if (j > begin)
        sort_quick_iterator(begin, j + 1);
    if (i < end)
        sort_quick_iterator(i, end);
}


int main() {
    constexpr const auto n = 100000;

    std::vector<int> v, v1, v2, v3;
    v.resize(n);

    for (size_t i = 0; i < v.size(); ++i)
        v[i] = std::rand() % (n + 1);

    std::cout << "Количество элементов: " << v.size() << std::endl;

    v1 = v; v2 = v; v3 = v;

    std::clock_t c = clock();
    sort_bubble(v1.begin(), v1.end());
    std::cout << "Пузырек - время работы: " << (clock() - c) / 1e6 << " секунд" << std::endl;

    c = clock();
    //sort_quick(v2, 0, v2.size() - 1);
    sort_quick_iterator(v2.begin(), v2.end());
    std::cout << "Быстрая сортировка (итераторы) - время работы: " << (clock() - c) / 1e6 << " секунд" << std::endl;

    assert(v1 == v2);

    c = clock();
    sort_quick(v3, 0, v2.size() - 1);
    std::cout << "Быстрая сортировка (индексы) - время работы: " << (clock() - c) / 1e6 << " секунд" << std::endl;

    assert(v1 == v3);

    return 0;
}
