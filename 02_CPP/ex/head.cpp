#include <string>
#include <iostream>
#include <fstream>

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

    // ファイルの先頭n行を読み込んで標準出力
    std::string input_path = argv[1];
    std::ifstream ifs(input_path); // stream
    std::string line;              // buffer
    while (std::getline(ifs, line, '\n'))
        if (n-- > 0)
            std::cout << line << std::endl;

    return 0;
}

// better implementation
// ファイル入力と標準出力を交互に行なうべきではない
// 入力は一度vectorにまとめて格納し，そのあとで出力すべき
