#include <string>
#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " filename [n]" << std::endl;
        return 1;
    }

    int n = 10;
    if (argc >= 3)
        n = std::stoi(argv[2]);

    // ファイル入力
    std::string input_path = argv[1];
    std::ifstream ifs(input_path); // stream
    std::string line;              // buffer
    std::vector<std::string> lines;
    while (std::getline(ifs, line, '\n'))
    {
        lines.push_back(line);
        if (lines.size() == n)
            break;
    }

    // 標準出力
    for (auto line : lines)
        std::cout << line << std::endl;

    return 0;
}