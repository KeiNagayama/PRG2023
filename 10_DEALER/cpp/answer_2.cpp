#include <stdio.h>
#include <vector>
#include <random>
#include <fstream>
#include <string>

std::mt19937 mt(1129);
std::uniform_real_distribution<> uni(0.0, 1.0);
std::string PRICE_CSV = "price_2.csv";

class DealerModel
{
public:
    std::vector<double> _market_price_vector;
    DealerModel(int N, double s, double c, double d, double dp, double dt, int M, double p0, int max_tick = 10000)
    {
        _N = N;
        _s = s;
        _c = c;
        _d = d;
        _dp = dp;
        _dt = dt;
        _dt = dt;
        _M = M;
        _p0 = p0;
        _tick = 0;
        _max_tick = max_tick;
        for (int i = 0; i < N; i++)
            _mid_price_vector.push_back(p0);
    }
    // method
    void run();

private:
    int _N;
    double _s;
    double _c;
    double _d;
    double _dp;
    double _dt;
    int _M;
    double _p0;
    int _max_tick;
    int _tick;
    std::vector<double> _mid_price_vector;
    // method
    int transaction();
    void trend_follow_random_walk();
};

void DealerModel::trend_follow_random_walk()
{
    int n;
    double trend = 0;
    if (_tick - 1 < _M)
        n = _tick - 1;
    else
        n = _M;
    for (int k = 0; k < n; k++)
    {
        double dP = _market_price_vector[(_tick - 1) - k] - _market_price_vector[(_tick - 1) - k - 1];
        trend += 2 * dP * (_M - k) / (_M * (_M + 1));
    }
    for (int i = 0; i < _N; i++)
    {
        if (uni(mt) < 0.5)
            _mid_price_vector[i] += _d * trend * _dt + _dp * _c;
        else
            _mid_price_vector[i] += _d * trend * _dt - _dp * _c;
    }
}

int DealerModel::transaction()
{
    double best_ask = _mid_price_vector[0] + _s / 2;
    double best_bid = _mid_price_vector[0] - _s / 2;
    int best_ask_idx = 0;
    int best_bid_idx = 0;
    for (int i = 0; i < _N; i++)
    {
        if (_mid_price_vector[i] + _s / 2 < best_ask)
        {
            best_ask = _mid_price_vector[i] + _s / 2;
            best_ask_idx = i;
        }
        else if (_mid_price_vector[i] - _s / 2 > best_bid)
        {
            best_bid = _mid_price_vector[i] - _s / 2;
            best_bid_idx = i;
        }
    }
    if (best_ask <= best_bid)
    {
        double market_price = (best_ask + best_bid) / 2;
        _market_price_vector.push_back(market_price);
        _mid_price_vector[best_ask_idx] = market_price;
        _mid_price_vector[best_bid_idx] = market_price;
        _tick++;
        printf("tick:%d, price:%f\r", _tick, market_price);
        return 1;
    }
    else
        return 0;
}

void DealerModel::run()
{
    while (1)
    {
        if (transaction())
            continue;
        else
            trend_follow_random_walk();
        if (_tick >= _max_tick)
        {
            printf("%s", "END");
            break;
        }
    }
}

int main()
{
    int N = 2;
    double s = .01;
    double c = .01;
    double d = 1.25;
    double dp = .01;
    double dt = .01 * .01;
    int M = 1;
    double p0 = 100.0;
    int max_tick = 10000;
    DealerModel model(N, s, c, d, dp, dt, M, p0);
    model.run();
    std::ofstream price_csv(PRICE_CSV);
    price_csv << "tick,market_price" << std::endl;
    for (int i = 0; i < max_tick; i++)
    {
        price_csv << i + 1 << "," << model._market_price_vector[i] << std::endl;
    }
}