#include "backtest/Portfolio.cpp"
#include "util/RunConfig.h"

int main(int argc, char *argv[]) {
    RunConfig small = RunConfig(0.5,
                                0.5,
                                9,
                                2,
                                -1,
                                -1,
                                "../resources/test_asset_returns.csv");
    RunConfig medium = RunConfig(0.5,
                                 0.5,
                                 50,
                                 4,
                                 -1,
                                 -1,
                                 "../resources/medium_asset_returns.csv");
    RunConfig large = RunConfig(0.5,
                                0.5,
                                700,
                                83,
                                12,
                                100,
                                "../resources/asset_returns.csv");

    Portfolio b = Portfolio(large);

    int n = 21;

    cout << "Target Return,\t IS Return,\t IS Std,\t OOS Return,\t OOS Std" << endl;
    for (int i = 0; i < n; i++) {
        double targetRet = i * 0.005;
        Results results = b.run(targetRet);
        cout << targetRet << ",\t " << results.retIS << ",\t " << results.stdIS
             << ",\t " << results.retOOS << ",\t " << results.stdOOS << endl;
    }


    return 0;
}

