#include <iostream> // 標準入出力
#include <fstream>  // ファイル入出力
#include <sstream>  // 文字列の分解に使う
#include <string>
#include <vector>

// 1つの文字列を区切り文字で分割し，vectorに格納する
// 例: {"2023", "4", "26"} = split("2023,4,26", ',')
// 例: {"2023", "4", "26"} = split("2023/4/26", '/')
std::vector<std::string> split(std::string str, char delim = ',')
{
    std::vector<std::string> items;
    std::stringstream ss(str);
    std::string item;
    while (std::getline(ss, item, delim))
        if (!item.empty())
            items.push_back(item);
    return items;
}

// パスで指定したcsvファイルを読み込む
std::vector<std::vector<std::string>> read_csv(std::string path)
{
    std::vector<std::vector<std::string>> data;
    std::ifstream ifs(path);
    std::string line;
    while (std::getline(ifs, line, '\n'))
        data.push_back(split(line, ','));
    return data;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Required: csv file path" << std::endl;
        return 0;
    }

    // データ読み込み
    std::string path = argv[1];
    std::vector<std::vector<std::string>> data = read_csv(path);

    // 行/列数を出力
    if (!data.empty())
    {
        std::cout << "#rows = " << data.size() << std::endl;
        std::cout << "#cols = " << data[0].size() << std::endl;
    }

    return 0;
}
