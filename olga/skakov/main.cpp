#include <iostream>

#define __cdecl __attribute__((__cdecl__))

extern "C" void __cdecl printasm(char *out_buf, const char *format, const char *hex_number); // const char *format,

int main() {
    char numb[128] = "-100";
    char buf[128] = {};
    const char *fmt = " 10";

    printasm(buf, fmt, numb);

    std::cout << "out: " << buf << std::endl;
}
