#include <iostream>

void decrelation()
{
    // int型の使用例
    int age = 20;
    int new_age = age + 10;
    // double型の使用例
    double height = 170.5;
    double new_height = height + 5.0;

    // bool型の使用例
    bool is_active = true;
    bool has_error = false;
    // char型の使用例
    char letter = '\n';
}

// 例：べき乗を計算（ただし，底，指数ともに非負整数）
// ** オーバーフローに注意 **
// power(10, 9)  = 1000000000
// power(10, 10) = 1410065408
int power(int base, int exponent)
{
    if (exponent <= 0)
        return 1;
    return base * power(base, exponent - 1);
}

// "="の仕切りを標準出力
void print_partition(int length = 30)
{
    for (int i = 0; i < length; i++)
    {
        std::cout << '=';
    }
    std::cout << std::endl;
}

void update(int a, int &b)
{
    ++a;
    ++b;
}

int main()
{
    int a = 0;
    int b = 0;
    update(a, b);
    std::cout << a << std::endl; // 0
    std::cout << b << std::endl; // 1
    return 0;
}
