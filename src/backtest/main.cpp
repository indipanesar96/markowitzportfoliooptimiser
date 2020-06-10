#include "Portfolio.cpp"
#include "../util/VectorUtil.h"
#include "../estimator/ParameterEstimator.h"
#include <chrono>

using namespace std;

void multipleRuns(int nRuns, vector<double> assets, RunConfig config);

int main(int argc, char *argv[]) {


    RunConfig small = RunConfig{0.5,
                                0.5,
                                9,
                                2,
                                2,
                                1,
                                "../resources/test_asset_returns.csv"};
    RunConfig medium = RunConfig{0.5,
                                 0.5,
                                 50,
                                 4,
                                 5,
                                 2,
                                 "../resources/medium_asset_returns.csv"};
    RunConfig full = RunConfig(0.5,
                               0.5,
                               700,
                               83,
                               12,
                               100,
                               "../resources/asset_returns.csv");


    int nRuns = 5;
//    vector<double> assets = vector<double>{2, 5, 8, 16, 32, 64};
    vector<double> assets = vector<double>{83, 83, 83, 83, 83, 83};

    multipleRuns(nRuns, assets, full);


    return 0;
}

void multipleRuns(int nRuns, vector<double> assets, RunConfig config) {

    int nTargetReturns = 21;
    double step = 0.005;
    vector<double> times = vector<double>(nRuns);

    for (int n = 0; n < nRuns; n++) {
        chrono::steady_clock::time_point begin = chrono::steady_clock::now();


        config.setNAssets(assets[n]);
        Portfolio portfolio = Portfolio(config);

        cout << "Target Return,\t IS Return,\t IS Var,\t OOS Return,\t OOS Var, \t nAssets: " << assets[n] << endl;
        for (int rp = 0; rp < nTargetReturns; rp++) {

            double targetRet = rp * step;
            BacktestResults results = portfolio.backtest(targetRet);
            cout << targetRet << ",\t " << results.retIS << ",\t " << results.stdIS
                 << ",\t " << results.retOOS << ",\t " << results.stdOOS << endl;
        }

        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        double timeTaken = chrono::duration_cast<chrono::milliseconds>(end - begin).count();

        cout << "Time taken: " << timeTaken << "[ms]" << endl;
        cout << endl;
        times[n] = timeTaken;
    }

    cout << "Mean of " << nRuns << " runs: " << ParameterEstimator::calculateMean(&times) << " ms" << endl;
    cout << "Std of " << nRuns << " runs: " << ParameterEstimator::calculateStd(&times) << " ms" << endl;

    cout << "Times:" << endl;
    printVector<double>(&times);
}