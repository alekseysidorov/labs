#include <iostream>
#include <bitset>
#include <vector>
#include <map>

#include <cmath>

int main() {
    uint64_t n, x;
    //std::cin >> n >> x;
    n = 6; x = 12;

    size_t x_s = std::sqrt(x);

    std::vector<bool> n_prime_set;
    n_prime_set.resize(x_s, false);
    n_prime_set[0] = true;
    n_prime_set[1] = true;
    for (size_t i = 2; i < x_s; ++i) {
        if (!n_prime_set[i]) {
            const size_t i2 = i * i;
            if (i2 < x) {
                for (size_t j = i2; j < x_s; j += i)
                    n_prime_set[j] = true;
            }
        }
    }

    std::map<size_t, size_t> prime_count;
    prime_count[1] = 1;
    std::cout << "Простые множители числа x=" << x << std::endl;

    auto x1 = x;
    for (size_t i = 1; i < x_s; ++i) {
        if (!n_prime_set[i]) {
            while ((x1 % i) == 0) {
                x1 /= i;
                prime_count[i] += 1;
                std::cout << i << " " << std::flush;
            }
        }
    }
    if (x1 != 1) {
        prime_count[x1] += 1;

        std::cout << x1 << " " << std::flush;
    }

    std::cout << std::endl;
    return 0;
}
