#include <iostream>
#include <string>


int main() {
    const std::string pattern = "hello";

    std::string s;
    std::cin >> s;

    const auto end = pattern.end();
    auto it = pattern.begin();
    for (const auto c : s) {
        if (*it == c) {
            it++;
            if (it == end) {
                std::cout << "YES" << std::endl;
                return 0;
            }
        }
    }

    std::cout << "NO" << std::endl;
    return 0;
}
