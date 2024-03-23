#include <iostream>

void numerics()
{
    // 除算
    std::cout << 2 / 3 << std::endl;    // 0
    std::cout << -2 / 3 << std::endl;   // 0
    std::cout << 2.0 / 3 << std::endl;  // 0.666667
    std::cout << -2 / 3.0 << std::endl; // -0.666667

    // 剰余
    std::cout << 2 % 3 << std::endl;   //  2
    std::cout << 2 % -3 << std::endl;  //  2
    std::cout << -2 % 3 << std::endl;  // -2
    std::cout << -2 % -3 << std::endl; // -2
}

void inc()
{
    // int a = 0;
    // ++a; // 前置インクリメント
    // a++; // 後置インクリメント
    // --a; // 前置デクリメント
    // a--; // 後置デクリメント

    // std::cout << a << std::endl; // 1

    int a = 0;
    int b; // 宣言だけして初期化しない

    b = ++a; // aをインクリメントしてからbに代入

    std::cout << a << std::endl; // 1
    std::cout << b << std::endl; // 1

    b = a++; // aをbに代入してからaをインクリメント

    std::cout << a << std::endl; // 2
    std::cout << b << std::endl; // 1

    // ++a;   // aをインクリメント
    // b = a; // bに代入
    // // a = 1, b = 1

    // b = a; // bに代入
    // ++a;   // aをインクリメント
    // // a = 2, b = 1
}

void booleans()
{
    bool A = true;
    bool B = false;
    bool not_A = !A;       // false
    bool A_and_B = A && B; // false
    bool A_or_B = A || B;  // true

    // 出力時は true→1, false→0 と置き換えられる
    std::cout << not_A << std::endl;   // 0
    std::cout << A_and_B << std::endl; // 0
    std::cout << A_or_B << std::endl;  // 1
}

void delimeters()
{
    char delim = ','; // カンマ区切り
    delim = ' ';      // スペース区切り
    delim = '\n';     // 行単位で区切る
}

void test_while()
{
    int i = 0;
    while (true)
    {
        i++;
    }
}

int main()
{
    // numerics();
    inc();
    // booleans();

    if (true)
        std::cout << "h" << std::endl;

    return 0;
}