#include "backtest/Backtester.cpp"
#include "util/RunConfig.h"

int main(int argc, char *argv[]) {
    RunConfig small = RunConfig(0.5, 0.5, 9, 2, "../resources/test_asset_returns.csv");
    RunConfig medium = RunConfig(0.5, 0.5, 50, 4, "../resources/medium_asset_returns.csv");
    RunConfig large = RunConfig(0.5, 0.5, 700, 83, "../resources/asset_returns.csv");

    double targetReturn = 0.0001;
    Backtester b(large);
//    b.run(small, targetReturn);
//    b.run(medium, targetReturn);
    b.run(targetReturn);

    return 0;
}

