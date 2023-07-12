#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>

std::mt19937 mt(1129);
std::uniform_real_distribution<> uni(0.0, 1.0);

int transaction(int N, double spread, std::vector<double> &mid_price_vec, std::vector<double> &market_price_vec, int &tick)
{
    double half_spread = spread / 2;
    double best_ask = mid_price_vec[0] + half_spread;
    int best_asker_idx = 0;
    double best_bid = mid_price_vec[0] - half_spread;
    int best_bidder_idx = 0;

    // calculate best_bid, best_ask
    for (int i = 0; i < N; i++)
    {
        // update best_ask
        double ask = mid_price_vec[i] + half_spread;
        if (ask < best_ask)
        {
            best_ask = ask;
            best_asker_idx = i;
            continue;
        }
        // update best_bid
        double bid = mid_price_vec[i] - half_spread;
        if (bid > best_bid)
        {
            best_bid = bid;
            best_bidder_idx = i;
        }
    }

    // no transaction occured
    if (best_ask > best_bid)
        return 0;

    // transaction and re-order
    double market_price = (best_ask + best_bid) / 2;
    market_price_vec.push_back(market_price);
    mid_price_vec[best_asker_idx] = market_price;
    mid_price_vec[best_bidder_idx] = market_price;
    tick++;
    printf("tick:%d, price:%f\r", tick, market_price);
    return 1;
}

void trend_follow_random_walk(double const &d, double const &dp, double const c, double const dt, int const N, int const M, int const tick,
                              std::vector<double> &mid_price_vec,
                              std::vector<double> &market_price_vec)
{
    // calculate trend <dP>_M
    double trend = 0;
    int m = (tick <= M) ? tick - 1 : M; // = min(tick-1,M)
    for (int k = 0; k < m; k++)
    {
        double dP = market_price_vec[(tick - 1) - k] - market_price_vec[(tick - 1) - k - 1];
        trend += (M - k) * dP;
    }
    trend *= 2 / (M * (M + 1));

    // update prices
    for (int i = 0; i < N; i++)
    {
        mid_price_vec[i] += d * trend * dt;
        mid_price_vec[i] += (uni(mt) < 0.5) ? dp * c : -dp * c;
    }
}

void output_vector(std::vector<double> &v, std::string path)
{
    std::ofstream ofs(path);
    for (auto x : v)
        ofs << x << std::endl;
}

int main()
{
    // initial parameters
    int N = 4;
    double dp = 0.01;
    double d = 1.25;
    double c = 0.01;
    double dt = 0.01 * 0.01;
    int M = 1;
    double spread = 0.01;
    double p0 = 100.0;
    int max_tick = 10000;

    // containers
    std::vector<double> mid_price_vector(N, p0);
    std::vector<double> market_price_vector;

    // simulation
    int tick = 0;
    while (tick < max_tick)
    {
        if (transaction(N, spread, mid_price_vector, market_price_vector, tick)) // transaction occured
            continue;
        trend_follow_random_walk(d, dp, c, dt, N, M, tick, mid_price_vector, market_price_vector);
    }

    // output market prices
    std::string path_market_price = "tickwise_marketprice";
    output_vector(market_price_vector, path_market_price);

    return 0;
}
