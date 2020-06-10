import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

figsize = (8, 6)
colour2 = r"m"
colour1 = r"c"
colour3 = r"C6"
colour4 = r"C8"

# Just some code to generate the plots


def read(filename, sep=','):
    df = pd.read_csv(filename, sep=sep)
    df.columns = [i.strip() for i in df.columns]
    return df


def plot_ef():
    plt.figure(2, figsize=figsize)
    plt.errorbar(timings['OOS Var'], timings['OOS Return'],
                 yerr=timings['OOS Var'] / len(timings['OOS Var']), label=r"Out Of Sample", c=colour1, ecolor=colour1)
    plt.xlabel(r"Portfolio Variance")
    plt.ylabel(r"Portfolio Returns")
    # plt.legend(loc=r'best')
    plt.title(r"Efficient Frontier")
    plt.savefig(r"../latex/figures/oos_ef.png", dpi=200)
    plt.savefig(r"oos_ef.png", dpi=200)

    plt.figure(5, figsize=figsize)
    plt.errorbar(timings['IS Var'], timings['IS Return'],
                 yerr=timings['IS Var'] / len(timings['IS Var']), label=r"In Sample", c=colour1, ecolor=colour1)
    plt.xlabel(r"Portfolio Variance")
    plt.ylabel(r"Portfolio Returns")
    # plt.legend(loc=r'best')
    plt.title(r"Efficient Frontier")
    plt.savefig(r"../latex/figures/is_ef.png", dpi=200)
    # plt.savefig(r"is_ef.png", dpi=200)
    plt.tight_layout()


def plot_linear():
    plt.figure(3, figsize=figsize)
    plt.errorbar(timings['Target Return'], timings['OOS Return'],
                 yerr=timings['OOS Var'] / len(timings['OOS Var']), ecolor=colour1, label=r"Out Of Sample", c=colour1)

    plt.errorbar(timings['Target Return'], timings['IS Return'],
                 yerr=timings['IS Var'] / len(timings['IS Var']), ecolor=colour2, linestyle="--",
                 label=r"In Sample", c=colour2)
    plt.plot(timings['Target Return'], timings['Target Return'], c="gray", label=r'Target')
    plt.xlabel(r"Target Return")
    plt.ylabel(r"Portfolio Returns")
    plt.title(r"Target Return Accuracy")
    plt.legend(loc=r'best')
    plt.savefig(r"../latex/figures/oos_accuracy.png", dpi=200)
    # plt.savefig(r"oos_accuracy.png", dpi=200)
    plt.tight_layout()


def fit_polynomial(df):
    degree_to_mse = pd.DataFrame()
    for d in range(1, 4):
        coeffs = np.polyfit(df["nAssets"], df["time [ms]"], deg=d, full=False)
        fitted_poly = np.poly1d(coeffs)

        print(d)
        print(f"These are the coefficients: ")
        print(fitted_poly.coeffs)

        df[f'Fitted: {d}'] = df["nAssets"].apply(lambda nAsset: fitted_poly(nAsset))

        degree_to_mse[d] = [d, sum([(i - j) ** 2 for i, j in zip(df["time [ms]"], df[f'Fitted: {d}'])])]

    degree_to_mse = degree_to_mse.transpose()

    return degree_to_mse, df


def plot_order():
    f, (ax0, ax1) = plt.subplots(nrows=2, ncols=1, figsize=(11, 10))
    ax0.plot(assets_variation['nAssets'], assets_variation['time [ms]'], label=r'Actual', c=colour1)
    ax0.plot(assets_variation['nAssets'], assets_variation[f'Fitted: 1'], linestyle="-.",
             label=f'(Order, MSE rank): (1, 3)', c=colour2)
    ax0.plot(assets_variation['nAssets'], assets_variation[f'Fitted: 2'], linestyle="--",
             label=f'(Order, MSE rank): (2, 1)', c=colour3)
    ax0.plot(assets_variation['nAssets'], assets_variation[f'Fitted: 3'], label=f'(Order, MSE rank): (3, 2)', c=colour4)

    ax0.set_xlabel("Number of assets considered")
    ax0.set_ylabel("Time taken to complete backtest [ms]")
    ax0.legend(loc=r'best')
    ax0.set_title("Investigating the time complexity in number of assets considered")

    ax1.plot(assets_variation['nAssets'], assets_variation['time [ms]'] - assets_variation['time [ms]'],
             label=r'Actual', c=r'black')
    ax1.plot(assets_variation['nAssets'], assets_variation[f'Fitted: 1'] - assets_variation['time [ms]'],
             linestyle="-.",
             label=f'(Order, MSE rank): (1, 3)', c=colour2)
    ax1.plot(assets_variation['nAssets'], assets_variation[f'Fitted: 2'] - assets_variation['time [ms]'],
             linestyle="--",
             label=f'(Order, MSE rank): (2, 1)', c=colour3)
    ax1.plot(assets_variation['nAssets'], assets_variation[f'Fitted: 3'] - assets_variation['time [ms]'],
             label=f'(Order, MSE rank): (3, 2)', c=colour4)

    ax1.set_xlabel("Number of assets considered")
    ax1.set_ylabel("Difference between fits and actual [ms]")
    ax1.legend(loc=r'best')
    ax1.set_title(r"Residual between fit and actual")

    plt.savefig(r"../latex/figures/time_complexity_in_assets.png", dpi=200)
    # plt.savefig(r"time_complexity_in_assets.png", dpi=200)
    plt.tight_layout()


def plot_shorts():
    plt.figure(9, figsize=(10, 6))
    plt.plot(nShorts['rp'], nShorts['aveShorts'], c=colour1)
    plt.xlabel(r"Target Portfolio Return, $r_p$")
    plt.ylabel(r"Mean Number of Short Positions")
    plt.title(r"Effect of Target Return level on Number of Short Positions")
    plt.savefig(r"../latex/figures/nShorts.png", dpi=200)
    plt.tight_layout()


def plot_evolution():
    f, ax = plt.subplots(nrows=2, ncols=2, figsize=(15, 10))

    targets = ['0.025', '0.05', '0.075', '0.1']

    for t, ax in zip(targets, ax.flatten()):
        ax.plot(all_market_returns.index, all_market_returns[t], label="Market", c=colour1)
        ax.plot(all_port_returns.index, all_port_returns[t], label="Portfolio", c=colour2)
        ax.axhline(y=float(t), linestyle='--', label="Target", c=r'black')
        ax.axhline(y=all_market_returns[t].mean(), linestyle='--', label="Market Mean", c=colour1)
        ax.axhline(y=all_port_returns[t].mean(), linestyle='--', label="Portfolio Mean", c=colour2)
        ax.set_xlabel(r"Test window")
        ax.set_ylabel(r"Daily Return")
        ax.legend(loc=r"best")
        ax.set_title(f"Target Return: {float(t) * 100}%")
        ax.set_ylim(bottom=-0.15, top=0.15)
    plt.savefig(r"../latex/figures/plot_evolution.png", dpi=200)
    plt.tight_layout()


timings = read(r"results.csv")
assets_variation = read(r"varying_assets.csv")
nShorts = read(r"nShorts.csv")

all_market_returns = read(r"mktReturnsAllWindowsAllTargets.csv")
all_port_returns = read(r"portfolioReturnsAllWindowsAllTargets.csv")

mse, fitted_asset_variation = fit_polynomial(assets_variation)
plot_shorts()
plot_evolution()

plot_order()
plot_ef()
plot_linear()
plt.show()
