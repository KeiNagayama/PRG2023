#include <iostream> // 標準入出力
#include <fstream>  // ファイル入出力
#include <sstream>  // 文字列の分解に使う
#include <string>
#include <vector>

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

// データから気温（3列目，index=2）だけ抽出する
std::vector<double> extract_temperatures(std::vector<std::vector<std::string>> &data)
{
    std::vector<double> temperatures;
    for (auto row : data)
    {
        temperatures.push_back(std::stod(row[2]));
    }
    return temperatures;
}

// 差分時系列を計算
std::vector<double> calc_diff_time_series(std::vector<double> &ts)
{
    std::vector<double> diff_ts;
    double prev = ts[0];
    for (int i = 1; i < ts.size(); i++)
    {
        diff_ts.push_back(ts[i] - prev);
        prev = ts[i];
    }
    return diff_ts;
}

// 差分時系列を出力
void output_vector(std::vector<double> &v, std::string path = "")
{
    if (path == "")
    {
        for (auto x : v)
            std::cout << x << std::endl;
        return;
    }
    std::ofstream ofs(path);
    for (auto x : v)
        ofs << x << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
        return 0;

    // データ読み込み
    std::string path = argv[1];
    std::vector<std::vector<std::string>> data = read_csv(path);
    std::vector<double> temperatures = extract_temperatures(data);

    // 差分時系列を計算
    std::vector<double> diff_temperatures = calc_diff_time_series(temperatures);

    // 標準出力
    std::string outpath = (argc < 3) ? "" : argv[2];
    output_vector(diff_temperatures, outpath);

    return 0;
}
