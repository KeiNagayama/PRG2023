#include <iostream>

int main()
{
    // calculate factorials from 1 to 20
    long factorial = 1;
    for (int i = 1; i <= 20; i++)
    {
        factorial *= i;
        std::cout << i << "! = " << factorial << std::endl;
    }

    return 0;
}

// #include <iostream>
// #include <iomanip> // setprecision()

// int main()
// {
//     // calculate factorials from 1 to 20
//     double factorial = 1;
//     std::cout << std::setprecision(20);
//     for (int i = 1; i <= 20; i++)
//     {
//         factorial *= i;
//         std::cout << i << "! = " << factorial << std::endl;
//     }

//     return 0;
// }