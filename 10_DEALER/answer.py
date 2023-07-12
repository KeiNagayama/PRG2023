import numpy as np


def transaction(mid_price_list, best_ask, best_bid):
    best_ask_id = np.argmin(mid_price_list)
    best_bid_id = np.argmax(mid_price_list)
    deal_price = (best_ask + best_bid) / 2
    mid_price_list[best_ask_id] = deal_price
    mid_price_list[best_bid_id] = deal_price


def random_walk(mid_price_list, c, dp, N):
    mid_price_list += c * np.random.choice([dp, -dp], N)


def trend_follow(mid_price_list, d, dt, M, price_list):
    dp_list = np.diff(price_list)
    n = len(dp_list) if M >= len(dp_list) else M
    trend = sum([(2 * dp_list[-(k + 1)] * (M - k)) / (M * (M + 1)) for k in range(n)])
    mid_price_list += d * trend * dt


def dealer_model(N, d, M, s, c, dp, dt, p0, max_tick=10000):
    """
      ディーラーモデルによるシミュレーションを行う
    """
    mid_price_list = np.ones(N)*p0
    market_price_list = []
    tick = 0
    while True:
        if tick >= max_tick:
            break
        best_ask = np.min(mid_price_list) + s/2
        best_bid = np.max(mid_price_list) - s/2
        if best_ask <= best_bid:
            transaction(mid_price_list, best_ask, best_bid)
            deal_price = (best_ask + best_bid) / 2
            market_price_list.append(deal_price)
            tick += 1
            print("\r""tick:{}/{}, price:{}".format(tick, max_tick, deal_price), end="")
            continue
        random_walk(mid_price_list, c, dp, N)
        trend_follow(mid_price_list, d, dt, M, market_price_list)
    return market_price_list


if __name__ == "__main__":
    np.random.seed(1129)
    P = dealer_model(N=2, d=1.25, M=2, s=0.01, c=0.01, dp=0.1, dt=0.1*0.1, p0=100)
