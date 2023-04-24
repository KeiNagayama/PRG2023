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

void output_vector(std::vector<int> &v)
{
    for (int i = 0; i < v.size(); i++)
    {
        std::cout << v[i] << std::endl;
    }
}

int main()
{
    int N = 10;
    std::vector<int> v = generate_serial_numbers(N);
    output_vector(v);

    return 0;
}