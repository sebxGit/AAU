#include <cstdint>
#include <iostream>

union S{
    float f;
    unsigned int i;
    char c[4];
};

void print_each_digit(int x)
{
    if(x >= 10)
        print_each_digit(x / 10);
    int digit = x % 10;
    std::cout << digit << '\n';
}

void f () {
    S s = {};
    s.i = 123456;
    print_each_digit(s.i); // it is big endian (most significant first)
}

int main() {
    f();
}