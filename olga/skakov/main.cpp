#include <iostream>

#define __cdecl __attribute__((__cdecl__))

extern "C" void __cdecl printasm(char *out_buf, char *format, const char *hex_number); // const char *format,

extern "C" void __cdecl abacaba(char *a, char *b)
{
    a[0] = 0xaa;
    b[0] = 0xff;
    a[1] = 0xbb;
    b[1] = 0xee;
}

int main() {
    char numb[128] = "164";
    char buf[128] = {};

    printasm(buf, numb);

    std::cout << buf << std::endl;
}
