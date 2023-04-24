#include <iostream>
#include <vector>
#include <map>

template <typename T>
void output_vector(std::vector<T> &v)
{
    for (auto x : v)
        std::cout << x << std::endl;
}

template <typename T0, typename T1>
void output_map(std::map<T0, T1> &mp)
{
    for (auto [key, value] : mp)
        std::cout << key << ": " << value << std::endl;
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

int main()
{
    std::vector<int> v0 = {0, 1, 2};
    std::vector<double> v1 = {3.14, 3.141, 3.1415};
    std::map<int, int> mp0 = {{0, 0}, {1, 1}, {2, 2}};
    std::map<int, double> mp1 = {{0, 3.14}, {1, 3.141}, {2, 3.1415}};

    output_vector(v0);
    output_vector(v1);
    output_map(mp0);
    output_map(mp1);

    output_vector(v0);
    print_partition(10);

    output_vector(v1);
    print_partition(10);

    output_map(mp0);
    print_partition(10);

    output_map(mp1);

    return 0;
}