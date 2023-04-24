#include <string>
#include <iostream>
#include <map>

// Apr-12 06:35 UTC
std::map<std::string, double> store_exchange_rate()
{
    std::map<std::string, double> rate;
    rate["JPY/USD"] = 133.77;
    rate["EUR/USD"] = 0.92;
    rate["CNH/USD"] = 6.89;
    return rate;
}

void output_map(std::map<std::string, double> &mp)
{
    for (auto p = mp.begin(); p != mp.end(); p++)
    {
        std::cout << p->first << ": " << p->second << std::endl;
    }
}

int main()
{
    std::map<std::string, double> rate = store_exchange_rate();
    output_map(rate);

    return 0;
}