#include <iostream> // 標準入出力
#include <fstream>  // ファイル入出力
#include <sstream>  // 文字列の分解に使う
#include <string>
#include <vector>
#include <map> // 連想配列(辞書)

// 1つの文字列を区切り文字で分割し，vectorに格納する
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
    std::ifstream ifs(path);
    std::string line;
    std::vector<std::vector<std::string>> data;
    while (std::getline(ifs, line))
        data.push_back(split(line, ','));
    return data;
}

// 月平均気温を求める
std::map<int, double> calc_monthly_averages(std::vector<std::vector<std::string>> &data)
{
    std::map<int, double> monthly_sum;
    std::map<int, double> monthly_cnt;
    for (auto &row : data)
    {
        auto ymd = split(row[0], '/');
        int ym = std::stoi(ymd[0]) * 100 + std::stoi(ymd[1]);
        double temperature = std::stod(row[2]);
        monthly_sum[ym] += temperature;
        monthly_cnt[ym]++;
    }
    std::map<int, double> monthly_average;
    for (auto [ym, sum] : monthly_sum)
    {
        monthly_average[ym] = sum / monthly_cnt[ym];
    }
    return monthly_average;
}

// mapを出力
void output_map(std::map<int, double> &mp, std::string path = "")
{
    if (path == "")
    {
        for (auto [key, value] : mp)
            std::cout << key << "," << value << std::endl;
        return;
    }
    std::ofstream ofs(path);
    for (auto [key, value] : mp)
        ofs << key << "," << value << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        return 0;
    }

    // データ読み込み
    std::string path = argv[1];
    std::vector<std::vector<std::string>> data = read_csv(path);

    // 月平均気温を求める
    std::map<int, double> monthly_averages = calc_monthly_averages(data);

    // 標準出力
    std::string outpath = (argc < 3) ? "" : argv[2];
    output_map(monthly_averages, outpath);

    return 0;
}
