#include <iostream>
#include <string>
#include <vector>
#include <map>

// vectorの要素数をカウントする
std::map<std::string, int> count_element(std::vector<std::string> &v)
{
    std::map<std::string, int> cnt;
    for (auto x : v)
    {
        cnt[x]++;
    }
    return cnt;
}

// mapのkey,valueを標準出力する
void output_map(std::map<std::string, int> &mp)
{
    for (auto [key, value] : mp)
    {
        std::cout << key << ": " << value << std::endl;
    }
}

int main()
{
    std::vector<std::string> words = {"AA", "BB", "CC", "AA"};
    std::map<std::string, int> word_counts = count_element(words);
    output_map(word_counts);

    return 0;
}