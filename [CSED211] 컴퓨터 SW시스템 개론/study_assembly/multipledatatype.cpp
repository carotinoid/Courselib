#include <iostream>
using data_t = double;
using data_t = char;
using data_t = long long;

int main() 
{
    data_t a = 'a';
    data_t b = 1e20;
    data_t c = 2147483650LL;
    printf("%c %lf %lld\n", a, b, c);
    return 0;
}
