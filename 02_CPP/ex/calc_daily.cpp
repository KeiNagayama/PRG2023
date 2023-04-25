#include <iostream> // 標準入出力
#include <fstream>  // ファイル入出力
#include <sstream>  // 文字列の分解に使う
#include <string>
#include <vector>
#include <map>   // 連想配列(辞書)
#include <cmath> // sqrt

// 1つの文字列を区切り文字で分割し，vectorに格納する
std::vector<std::string>
split(std::string str, char delim = ',')
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

struct Stats
{
    double min;
    double max;
    double mu;
    double stdev;
    Stats() {}
    Stats(std::vector<double> &v)
    {
        int N = v.size();
        if (N == 0)
            return;

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
        min = xmin;
        max = xmax;
        mu = sum / N;
        stdev = std::sqrt(sumsq / N - mu * mu);
    }
};

// 日ごとの統計量を求める
std::map<int, Stats> calc_daily_stats(std::vector<std::vector<std::string>> &data)
{
    std::map<int, std::vector<double>> daily_tempereture_vector;
    for (auto &row : data)
    {
        auto ymd = split(row[0], '/');
        int date = std::stoi(ymd[0]) * 10000 + std::stoi(ymd[1]) * 100 + std::stoi(ymd[2]);
        double temperature = std::stod(row[2]);
        daily_tempereture_vector[date].push_back(temperature);
    }

    std::map<int, Stats> daily_stats; // thsi needs constructor Stats(){}
    for (auto &[date, v] : daily_tempereture_vector)
    {
        daily_stats[date] = Stats(v);
    }
    return daily_stats;
}

// vector<Stats>を出力
void output_stats_map(std::map<int, Stats> &daily_stats, std::string path = "")
{
    if (path == "")
    {
        std::cout << "date,min,max,mu,std" << std::endl;
        for (auto &[date, stats] : daily_stats)
            std::cout << date << "," << stats.min << "," << stats.max << "," << stats.mu << "," << stats.stdev << std::endl;
        return;
    }
    std::ofstream ofs(path);
    ofs << "date,min,max,mu,std" << std::endl;
    for (auto [date, stats] : daily_stats)
        ofs << date << "," << stats.min << "," << stats.max << "," << stats.mu << "," << stats.stdev << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Error: input file not specified" << std::endl;
        return 0;
    }

    // データ読み込み
    std::string path = argv[1];
    std::vector<std::vector<std::string>> data = read_csv(path);

    // 日ごとの統計量を求める
    std::map<int, Stats> daily_stats = calc_daily_stats(data);

    // 標準出力 or ファイル出力
    std::string outpath = (argc < 3) ? "" : argv[2];
    output_stats_map(daily_stats, outpath);

    return 0;
}
