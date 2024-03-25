// #include <string>

// int main(int argc, char *argv[])
// {
//     if (argc < 2)
//         return 0;

//     std::string msg = "Hello World!";
//     std::string exe = argv[0];
//     int i = std::stoi(argv[1]);
//     double d = std::stod(argv[2]);

//     return 0;
// }

#include <iostream>
#include <string>
#include <sstream>

int main()
{
    std::string text = "123,456,789 ";
    std::stringstream ss(text);
    std::string element;

    int sum = 0;
    for (int i = 0; i < 3; ++i)
    {
        std::getline(ss, element, ',');
        std::cout << element << std::endl;
        sum += std::stoi(element);
    }
    std::string message = "sum = " + std::to_string(sum);
    std::cout << message << std::endl;
    return 0;
}

// #include <iostream>
// #include <string>
// #include <sstream>

// int main()
// {
//     std::string text = "123,456,789 ";
//     std::stringstream ss(text);
//     std::string element;
//     int sum = 0;
//     while (std::getline(ss, element, ','))
//     {
//         std::cout << element << std::endl;
//         sum += std::stoi(element);
//     }
//     std::string message = "sum = " + std::to_string(sum);
//     std::cout << message << std::endl;
//     return 0;
// }

// #include <iostream>
// #include <string>
// #include <sstream>

// int main()
// {
//     std::string s = "Hello world!";
//     std::string substr1 = s.substr(0, 5);
//     std::string substr2 = s.substr(6, 5);
//     std::string substr3 = s.substr(11, 1);
//     std::cout << substr1 << std::endl;
//     std::cout << substr2 << std::endl;
//     std::cout << substr3 << std::endl;
//     return 0;
// }
// // === 出力 ===
// // Hello
// // world
// // !