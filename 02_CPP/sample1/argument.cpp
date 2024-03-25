#include <iostream>

// "="の仕切りを標準出力
void print_partition(int length = 30)
{
    for (int i = 0; i < length; i++)
    {
        std::cout << '=';
    }
    std::cout << std::endl;
}

// int main(int argc, char *argv[])
// {
//     print_partition(20);
//     for (int i = 0; i < argc; i++)
//     {
//         std::string arg = argv[i];
//         std::cout << i << ": " << arg << std::endl;
//     }
//     print_partition(20);
//     return 0;
// }

#include <iostream>
int main(int argc, char *argv[])
{
    for (int i = 0; i < argc; ++i)
        printf("argv[%d] = %s\n", i, argv[i]);

    return 0;
}
