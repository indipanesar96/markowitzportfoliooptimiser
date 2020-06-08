import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

figsize = (8,6)

def read(filename):
    df = pd.read_csv(filename)
    df.columns = [i.strip() for i in df.columns]
    return df


def plot_ef():
    plt.figure(2, figsize=figsize)
    plt.errorbar(timings['OOS Var'], timings['OOS Return'],
                 yerr=timings['OOS Var'] / len(timings['OOS Var']), label=r"OOS")
    plt.xlabel(r"Portfolio Variance [%]")
    plt.ylabel(r"Portfolio Returns [%]")
    # plt.legend(loc=r'best')
    plt.title(r"Out Of Sample Efficient Frontier Derived from Markowitz Portfolio Optimisation")
    # plt.savefig(r"../latex/figures/oos_ef.png", dpi=200)
    plt.savefig(r"oos_ef.png", dpi=200)

    plt.figure(5, figsize=figsize)
    plt.errorbar(timings['IS Var'], timings['IS Return'],
                 yerr=timings['IS Var'] / len(timings['IS Var']), label=r"IS")
    plt.xlabel(r"Portfolio Variance [%]")
    plt.ylabel(r"Portfolio Returns [%]")
    # plt.legend(loc=r'best')
    plt.title(r"In Sample Efficient Frontier Derived from Markowitz Portfolio Optimisation")
    # plt.savefig(r"../latex/figures/is_ef.png", dpi=200)
    plt.savefig(r"is_ef.png", dpi=200)
    plt.tight_layout()


def plot_linear():
    plt.figure(3, figsize=figsize)
    plt.errorbar(timings['Target Return'], timings['OOS Return'],
                 yerr=timings['OOS Var'] / len(timings['OOS Var']), label=r"OOS")
    plt.plot(timings['Target Return'], timings['Target Return'], label=r'Benchmark')
    plt.xlabel(r"Target Return [%]")
    plt.ylabel(r"Portfolio Returns [%]")
    plt.title(r"Return Target Accuracy")
    plt.legend(loc=r'best')
    plt.savefig(r"oos_accuracy.png", dpi=200)
    plt.tight_layout()


def fit_polynomial(df):
    degree_to_mse = pd.DataFrame()
    for d in range(1, 4):
        coeffs = np.polyfit(df["nAssets"], df["time [ms]"], deg=d, full=False)
        fitted_poly = np.poly1d(coeffs)
        df[f'Fitted: {d}'] = df["nAssets"].apply(lambda nAsset: fitted_poly(nAsset))

        degree_to_mse[d] = [d, sum([(i - j) ** 2 for i, j in zip(df["time [ms]"], df[f'Fitted: {d}'])])]

    degree_to_mse = degree_to_mse.transpose()

    return degree_to_mse, df


def plot_order():
    f, (ax0, ax1) = plt.subplots(nrows=2, ncols=1, figsize=(13,10))
    ax0.plot(assets_variation['nAssets'], assets_variation['time [ms]'], label=r'Actual')
    ax0.plot(assets_variation['nAssets'], assets_variation[f'Fitted: 1'], linestyle="-.",
             label=f'(Order, MSE rank): (1, 3)')
    ax0.plot(assets_variation['nAssets'], assets_variation[f'Fitted: 2'], linestyle="--",
             label=f'(Order, MSE rank): (2, 2)')
    ax0.plot(assets_variation['nAssets'], assets_variation[f'Fitted: 3'], label=f'(Order, MSE rank): (3, 1)')

    ax0.set_xlabel("Number of assets considered")
    ax0.set_ylabel("Time taken to complete backtest [ms]")
    ax0.legend(loc=r'best')
    ax0.set_title("Investigating the time complexity in number of assets considered")

    ax1.plot(assets_variation['nAssets'], assets_variation['time [ms]'] - assets_variation['time [ms]'], label=r'Actual')
    ax1.plot(assets_variation['nAssets'], assets_variation[f'Fitted: 1'] - assets_variation['time [ms]'],
             linestyle="-.",
             label=f'(Order, MSE rank): (1, 3)')
    ax1.plot(assets_variation['nAssets'], assets_variation[f'Fitted: 2'] - assets_variation['time [ms]'],
             linestyle="--",
             label=f'(Order, MSE rank): (2, 2)')
    ax1.plot(assets_variation['nAssets'], assets_variation[f'Fitted: 3'] - assets_variation['time [ms]'],
             label=f'(Order, MSE rank): (3, 1)')

    ax1.set_xlabel("Number of assets considered")
    ax1.set_ylabel("Difference between fits and actual [ms]")
    ax1.legend(loc=r'best')
    ax1.set_title(r"Residual between fit and actual")

    # plt.savefig(r"../latex/figures/time_complexity_in_assets.png", dpi=200)
    plt.savefig(r"time_complexity_in_assets.png", dpi=200)
    plt.tight_layout()


timings = read(r"results.csv")
assets_variation = read(r"varying_assets.csv")

# timings['OOS Var'] = timings['OOS Std'].apply(lambda x: x ** 2)
# timings['IS Var'] = timings['IS Std'].apply(lambda x: x ** 2)

mse, fitted_asset_variation = fit_polynomial(assets_variation)
plot_order()
# plot_ef()
# plot_linear()
plt.show()
