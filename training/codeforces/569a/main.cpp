#include <iostream>
#include <string>


int main() {
    int t, s, q;
    std::cin >> t >> s >> q;

    q--;
    int i = 0;
    while (s < t) {
        int r = s*q;
        s+= r;
        ++i;
    }

    std::cout << i << std::endl;
    return 0;
}
