#include <iostream> // 標準入出力
#include <fstream>  // ファイル入出力
#include <sstream>  // 文字列の分解に使う
#include <string>
#include <vector>
#include <map> // 連想配列(辞書)

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

struct Daily_temperature
{
    int year;
    int month;
    int date;
    int time; // hourly
    double temperature;

    // "2017/1/1" -> 2017,1,1
    void set_ymd(std::string str_ymd)
    {
        auto ymd = split(str_ymd, '/');
        year = std::stoi(ymd[0]);
        month = std::stoi(ymd[1]);
        date = std::stoi(ymd[2]);
    }
    // "1:00" -> 1
    void set_time(std::string str_time)
    {
        time = std::stoi(split(str_time, ':')[0]);
    }
    // ""
    void set_temperature(std::string str_temperature)
    {
        temperature = std::stod(str_temperature);
    }
    Daily_temperature(std::vector<std::string> ymd_time_temperature, char delim = ',')
    {
        set_ymd(ymd_time_temperature[0]);
        set_time(ymd_time_temperature[1]);
        set_temperature(ymd_time_temperature[2]);
    }
};

// データを日ごとに整理する
std::vector<Daily_temperature> to_daily_temperatures(std::vector<std::vector<std::string>> &data)
{
    std::vector<Daily_temperature> daily_temperatures;
    for (auto row : data)
    {
        daily_temperatures.push_back(Daily_temperature(row));
    }
    return daily_temperatures;
}

// 月平均気温を求める
std::map<int, double> calc_monthly_averages(std::vector<Daily_temperature> &daily_temperatures)
{
    std::map<int, double> monthly_sum;
    std::map<int, double> monthly_cnt;
    for (auto &daily_temperature : daily_temperatures)
    {
        int ym = daily_temperature.year * 100 + daily_temperature.month;
        monthly_sum[ym] += daily_temperature.temperature;
        monthly_cnt[ym]++;
    }
    std::map<int, double> monthly_average;
    for (auto [ym, sum] : monthly_sum)
    {
        monthly_average[ym] = sum / monthly_cnt[ym];
    }
    return monthly_average;
}

// vectorを出力
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
        return 0;

    // データ読み込み
    std::string path = argv[1];
    std::vector<std::vector<std::string>> data = read_csv(path);
    std::vector<Daily_temperature> daily_temperatures = to_daily_temperatures(data);

    // 月平均気温を求める
    std::map<int, double> monthly_averages = calc_monthly_averages(daily_temperatures);

    // 標準出力
    std::string outpath = (argc < 3) ? "" : argv[2];
    output_map(monthly_averages, outpath);

    return 0;
}
