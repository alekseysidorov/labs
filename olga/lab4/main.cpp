#include <iostream>


int main()
{
    const char states[4][2] = {
        { 2, 1 }, //s1
        { 2, 1 }, //s2
        { 2, 3 }, //s3
        { 2, 1 }, //s4
    };

    unsigned char c;
    unsigned char s = 0;
    while (std::cin.peek() != '\n') {
        std::cin >> c;
        c -= '0';

        if (c > 1) {
            std::cout << "wrong!!" << std::endl;
            return -1;
        }


        s = states[s][c];
    }

    std::cout << "result state is s" << int(s + 1) << std::endl;
    return 0;
}

