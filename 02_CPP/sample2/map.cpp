#include <string>
#include <iostream>
#include <map>
#include <vector>

// Apr-12 06:35 UTC
std::map<std::string, double> store_exchange_rate()
{
    std::map<std::string, double> rate;
    rate["JPY/USD"] = 133.77;
    rate["EUR/USD"] = 0.92;
    rate["CNH/USD"] = 6.89;
    return rate;
}

// 2024年春アニメ
std::map<std::string, std::string> store_anime_url()
{
    std::map<std::string, std::string> to_url;
    to_url["魔法科3"] = "https://mahouka.jp/3rd/";
    to_url["ユーフォ3"] = "https://anime-eupho.com";
    to_url["獣と香辛料"] = "https://spice-and-wolf.com";
    // to_url["無職転生2"] = "https://mushokutensei.jp";
    // to_url["転スラ3"] = "https://www.ten-sura.com/anime/tensura";
    // to_url["このすば3"] = "http://konosuba.com/3rd/";
    // to_url["鬼滅4"] = "https://kimetsu.com/anime/hashirageikohen/";
    return to_url;
}

// void output_map(std::map<std::string, double> &mp)
// {
//     for (auto p = mp.begin(); p != mp.end(); p++)
//     {
//         std::cout << p->first << ": " << p->second << std::endl;
//     }
// }

template <typename T1, typename T2>
void output_map(std::map<T1, T2> &mp)
{
    for (auto [key, value] : mp)
    {
        std::cout << key << ": " << value << std::endl;
    }
}

int main()
{
    std::map<std::string, double> rate = store_exchange_rate();

    std::map<std::string, std::string> to_anime_url = store_anime_url();
    output_map(to_anime_url);

    std::vector<int> v = {2, 0, 2, 4, 0, 4, 0, 1};

    // 各要素の出現数をカウント
    std::map<int, int> cnt;
    for (int x : v)
        ++cnt[x]; // 初期値は 0

    // 出力
    for (auto [key, value] : cnt)
        std::cout << key << ": " << value << std::endl;

    return 0;
}