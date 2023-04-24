#include <string>
#include <iostream>
#include <fstream>

int main()
{
    // ファイル入力の例
    std::string input_path = "input.txt";
    std::ifstream ifs(input_path); // stream
    std::string line;              // buffer
    while (std::getline(ifs, line, '\n'))
        std::cout << line << std::endl;

    // ファイル出力の例
    std::string output_path = "output.txt";
    std::ofstream ofs(output_path);
    ofs << "Hello World!" << std::endl;
    return 0;
}
