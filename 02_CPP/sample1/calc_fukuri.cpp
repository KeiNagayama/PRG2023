#include <iostream>
#include <string>

// calculate a^n
double power(double x, int n)
{
    if (n == 0)
        return 1.0;
    return x * power(x, n - 1);
}

// calculate x*(1+r/100)^t
double fukuri(int x, int r, int t)
{
    return x * power(1.0 + r / 100.0, t);
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        std::cout << "元本，年利，運用期間を入力してください" << std::endl;
        return 1;
    }
    int x = std::stoi(argv[1]);
    int r = std::stoi(argv[2]);
    int t = std::stoi(argv[3]);
    if (x <= 0 || r <= 0 || t <= 0)
    {
        std::cout << "元本，年利，運用期間には正の整数を指定してください" << std::endl;
        return 1;
    }
    std::cout << fukuri(x, r, t) << std::endl;
    return 0;
}