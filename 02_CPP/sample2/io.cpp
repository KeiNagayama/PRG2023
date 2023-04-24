#include <iostream>

int main()
{
    double PI = 3.1415;
    std::cout << "PI = " << (int)PI << std::endl;
    std::cout << "PI = " << PI << std::endl;
    printf("PI = %1.0f\n", PI);
    printf("PI = %1.2f\n", PI);

    return 0;
}