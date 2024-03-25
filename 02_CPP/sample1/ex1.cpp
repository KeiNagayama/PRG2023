#include <iostream>
#include <string>

int factorial(int n)
{
    if (n == 0)
        return 1;
    return n * factorial(n - 1);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "整数を1つ指定してください" << std::endl;
        return 1;
    }
    int n = std::stoi(argv[1]);
    if (n < 0)
    {
        std::cout << "正の整数を指定してください" << std::endl;
        return 1;
    }
    std::cout << factorial(n) << std::endl;
    return 0;
}