#include <iostream>
#include <bitset>

#include <cmath>

int main() {
    constexpr const size_t m = 10000;

    std::bitset<m> prime(true);
    prime[0] = false;
    prime[1] = false;

    uint64_t n, x;
    std::cin >> n >> x;

    for (size_t i = 2; i < std::sqrt(x); ++i) {
        if (prime[i]) {
            const size_t i2 = i * i;
            if (i2 < x) {
                for (size_t j = i2; j < x; j += i)
                    prime[i] = false;
            }
        }
    }

    std::cout << "Простые множители числа x=" << x << std::endl;
    for (size_t i = 1; i < std::sqrt(x); ++i) {
        if (!prime[i])
            std::cout << i << " " << std::flush;
    }
    std::cout << std::endl;
    return 0;
}
