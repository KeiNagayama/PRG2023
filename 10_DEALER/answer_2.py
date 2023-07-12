import numpy as np


class DealerModel:
    def __init__(self, N, d, M, s, c, dp, dt, p0, max_tick=10000):
        self.N = N
        self.d = d
        self.M = M
        self.s = s
        self.c = c
        self.dp = dp
        self.dt = dt
        self.p0 = p0
        self.max_tick = max_tick
        self.mid_price_list = np.ones(N) * p0
        self.market_price_list = []

    @property
    def tick(self):
        return len(self.market_price_list)

    @property
    def best_ask(self):
        return np.min(self.mid_price_list) + self.s/2

    @property
    def best_bid(self):
        return np.max(self.mid_price_list) - self.s/2

    @property
    def best_ask_id(self):
        return np.argmin(self.mid_price_list)

    @property
    def best_bid_id(self):
        return np.argmax(self.mid_price_list)

    def transaction(self):
        deal_price = (self.best_ask + self.best_bid) / 2
        self.market_price_list.append(deal_price)
        self.mid_price_list[self.best_ask_id] = deal_price
        self.mid_price_list[self.best_bid_id] = deal_price
        print("\r""Tick:{}/{}, Price:{}".format(self.tick, self.max_tick, deal_price), end="")

    def random_walk(self):
        self.mid_price_list += self.c * np.random.choice([self.dp, -self.dp], self.N)

    def trend_follow(self):
        dp_list = np.diff(self.market_price_list)
        n = len(dp_list) if self.M >= len(dp_list) else self.M
        trend = sum([(2 * dp_list[-(k + 1)] * (self.M - k)) / (self.M * (self.M + 1)) for k in range(n)])
        self.mid_price_list += self.d * self.dt * trend

    def run(self):
        while True:
            if self.tick >= self.max_tick:
                break
            if self.best_ask < self.best_bid:
                self.transaction()
                continue
            self.random_walk()
            self.trend_follow()


if __name__ == "__main__":
    np.random.seed(1129)
    model = DealerModel(N=2, d=0, M=2, s=0.01, c=0.01, dp=0.1, dt=0.1*0.1, p0=100)
    model.run()
    market_price_list = model.market_price_list
