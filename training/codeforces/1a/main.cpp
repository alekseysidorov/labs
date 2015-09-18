#include <vector>

#include <iostream>

#include <cstdlib>


int main() {
    int64_t n, m, a;
    std::cin >> n >> m >> a;

    auto div1 = std::div(n, a);
    auto div2 = std::div(m, a);

    if (div1.rem > 0)
        div1.quot++;

    if (div2.rem > 0)
        div2.quot++;

    std::cout << div1.quot * div2.quot;
    return 0;
}
