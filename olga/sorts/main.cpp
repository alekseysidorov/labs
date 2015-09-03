#include <iostream>
#include <vector>
#include <ctime>
#include <cassert>
#include <cstdlib>

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

void merge2(std::vector<int> &v, std::vector<int> &tmp, size_t left, size_t mid, size_t right)
{
    size_t j = left, k = mid, i = 0;

    while (j < mid && k < right) {
        if (v[j] < v[k]) {
            tmp[i] = v[j];
            ++j;
        } else {
            tmp[i] = v[k];
            ++k;
        }
        ++i;
    }

    for (; j < mid; ++j, ++i)
        tmp[i] = v[j];
    for (; k < right; ++k, ++i)
        tmp[i] = v[k];

    for (j = 0; j < i; ++j)
        v[j + left] = tmp[j];
}

void sort_merge2(std::vector<int> &v, std::vector<int> &tmp, size_t left, size_t right)
{
    if ((right - left) == 1)
        return;

    size_t mid = (left + right) / 2;
    sort_merge2(v, tmp, left, mid);
    sort_merge2(v, tmp, mid, right);
    merge2(v, tmp, left, mid, right);
}

void sort_merge2(std::vector<int> &v)
{
    std::vector<int> tmp(v.size());
    sort_merge2(v, tmp, 0, v.size());
}

int main()
{
    std::vector<int> v, v1, v2;
    v.resize(10000);

    for (size_t i = 0; i < v.size(); ++i)
        v[i] = std::rand();

    std::cout << "Количество элементов: " << v.size() << std::endl;

    v1 = v; v2 = v;

    std::clock_t c = clock();
    sort_bubble(v);
    std::cout << "Пузырек - время работы: " << (clock() - c) / 1e6 << " секунд" << std::endl;

    c = clock();
    sort_merge(v1);
    std::cout << "Слияние - время работы: " << (clock() - c) / 1e6 << " секунд" << std::endl;

    assert(v == v1);

    c = clock();
    sort_merge2(v2);
    std::cout << "Слияние без доп памяти - время работы: " << (clock() - c) / 1e6 << " секунд" << std::endl;

    assert(v == v2);

    return 0;
}

