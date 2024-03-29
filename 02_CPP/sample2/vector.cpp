#include <iostream>
#include <vector>

std::vector<int> generate_serial_numbers(int n)
{
    std::vector<int> v;
    for (int i = 0; i < n; i++)
    {
        v.push_back(i);
    }
    return v;
}

void access_to_elements(std::vector<int> v)
{
    // 通常の for 文による要素アクセス
    for (int i = 0; i < v.size(); ++i)
    {
        v[i] *= 2;
    }
    // 範囲 for 文 (c++11以降)
    for (int &x : v) // 要素を参照型で受け取る
    {
        x *= 2;
    }
}
// void output_vector(std::vector<int> &v)
// {
//     for (int i = 0; i < v.size(); i++)
//     {
//         std::cout << v[i] << std::endl;
//     }
// }

void output_vector(std::vector<int> &v)
{
    for (auto x : v)
    {
        std::cout << x << std::endl;
    }
}

int main()
{
    int N = 10;
    std::vector<int> v = generate_serial_numbers(N);
    output_vector(v);

    return 0;
}