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

    Portfolio b(large);

    double start = 0.0;
    double end = 0.1;
    int n = 21;

    for (int i = 0; i < n; i++) {
        double targetRet = start + i * 0.005;
        double actual = b.run(targetRet);
        cout << "Target: " << targetRet << " Actual: " << actual << endl;
    }


    return 0;
}

