#include <iostream> // 標準入出力
#include <fstream>  // ファイル入出力
#include <sstream>  // 文字列の分解に使う
#include <string>
#include <vector>
#include <map>   // 連想配列，辞書
#include <cmath> // sqrt

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

// 年ごとの，気温が20度を超えた時刻の割合を計算
void calc_rate_above_threshold(std::vector<double> &temperatures, double threshold_degree = 20)
{
    int cnt_total = 0; // 代わりにtemperatures.size()を使ってもよい
    int cnt_above = 0;
    for (auto T : temperatures)
    {
        cnt_total++;
        if (T > threshold_degree)
            cnt_above++;
    }
    std::cout << "%(T>20): " << (double)cnt_above / cnt_total << std::endl;
}

// 年ごとの，気温の各種統計量を計算
void calc_statistics(std::vector<double> &v)
{
    int N = v.size();
    if (N == 0)
    {
        std::cout << "Given vector is empty." << std::endl;
        return;
    }

    double x = v[0];
    double xmin = x;
    double xmax = x;
    double sum = x;
    double sumsq = x * x;

    for (int i = 1; i < N; i++)
    {
        x = v[i];
        if (x < xmin)
            xmin = x;
        if (x > xmax)
            xmax = x;
        sum += x;
        sumsq += x * x;
    }

    double mu = sum / N;
    double var = sumsq / N - mu * mu;
    double stdev = std::sqrt(var); // stdは使用済み -> standard deviationの頭文字を取った
    std::cout << "min: " << xmin << std::endl;
    std::cout << "max: " << xmax << std::endl;
    std::cout << "mu : " << mu << std::endl;
    std::cout << "std: " << stdev << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "" << std::endl;
        return 0;
    }

    // データ読み込み
    std::string path = argv[1];
    std::vector<std::vector<std::string>> data = read_csv(path);
    std::vector<double> temperatures = extract_temperatures(data);

    // 計算
    calc_rate_above_threshold(temperatures, 20);
    calc_statistics(temperatures);

    return 0;
}
