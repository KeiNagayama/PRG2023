#include <iostream>
#include <cmath>

int main()
{
    double zeta2 = std::riemann_zeta(2); // c++17
    printf("zeta(2) = %.5f\n", zeta2);

    double pi = 3.141592;
    zeta2 = pi * pi / 6;
    printf("zeta(2) = %.5f\n", zeta2);

    return 0;
}