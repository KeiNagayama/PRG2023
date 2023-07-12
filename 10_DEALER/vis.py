import numpy as np
import matplotlib.pyplot as plt

TITLE_FONT_SIZE = 20
LABEL_FONT_SIZE = 18
TICK_FONT_SIZE = 14


def vis_tick_price(price_list):
    tick_list = range(len(price_list))
    fig = plt.figure(figsize=(8, 4), dpi=100, tight_layout=True)
    ax = fig.add_subplot(111)
    ax.plot(tick_list, price_list)
    ax.set_title("Market Price", fontsize=TITLE_FONT_SIZE)
    ax.set_xlabel("Tick", fontsize=LABEL_FONT_SIZE)
    ax.set_ylabel("Price", fontsize=LABEL_FONT_SIZE)
    ax.tick_params(labelsize=TICK_FONT_SIZE)
    plt.show()


def vis_volatility_cdf(price_list, scale="log"):
    dp_list = np.diff(price_list)
    vo_list = np.abs(dp_list)
    cdf_x = np.sort(vo_list)
    cdf_y = [1 - i/len(cdf_x) for i in range(len(cdf_x))]
    fig = plt.figure(figsize=(6, 5), dpi=100, tight_layout=True)  # width*height
    ax = fig.add_subplot(111)
    ax.plot(cdf_x, cdf_y)
    ax.set_title(r"CDF of $|\Delta p|$", fontsize=TITLE_FONT_SIZE)
    ax.set_xlabel(r"$|\Delta p|$", fontsize=LABEL_FONT_SIZE)
    ax.set_ylabel("CDF", fontsize=LABEL_FONT_SIZE)
    ax.tick_params(labelsize=TICK_FONT_SIZE)
    if scale == "log":
        ax.set_xscale("log")
        ax.set_yscale("log")
    elif scale == "semi":
        ax.set_yscale("log")
    plt.show()


def vis_auto_correlation(price_list, K=20):
    dp_list = np.diff(price_list)
    c0 = np.var(dp_list)
    auto = [(np.mean(dp_list[:-k]*dp_list[k:]) - np.mean(dp_list[:-k])*np.mean(dp_list[k:])) / c0 for k in range(1, K)]
    x = range(K)
    y = [1] + auto
    fig = plt.figure(figsize=(6, 5), dpi=100, tight_layout=True)  # width*height
    ax = fig.add_subplot(111)
    ax.plot(x, y)
    ax.set_title(r"Auto correlation of $\Delta p$", fontsize=TITLE_FONT_SIZE)
    ax.set_xlabel(r"$Lag K$", fontsize=LABEL_FONT_SIZE)
    ax.set_ylabel("auto correlation", fontsize=LABEL_FONT_SIZE)
    ax.tick_params(labelsize=TICK_FONT_SIZE)
    plt.show()


if __name__ == "__main__":
    import answer as ans
    np.random.seed(1129)
    market_price_list = ans.dealer_model(N=2, d=1.25, M=2, s=0.01, c=0.01, dp=0.1, dt=0.1*0.1, p0=100, max_tick=3000)
    vis_tick_price(market_price_list)
    vis_volatility_cdf(market_price_list, scale="normal")
    vis_volatility_cdf(market_price_list, scale="semi")
    vis_volatility_cdf(market_price_list, scale="log")
    vis_auto_correlation(market_price_list)
