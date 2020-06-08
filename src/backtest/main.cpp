#include "Portfolio.cpp"
#include "../util/VectorUtil.h"
#include "../estimator/ParameterEstimator.h"
#include <chrono>


int main(int argc, char *argv[]) {


    chrono::steady_clock::time_point begin = chrono::steady_clock::now();


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
    RunConfig full = RunConfig{0.5,
                               0.5,
                               700,
                               83,
                               12,
                               100,
                               "../resources/asset_returns.csv"};

    Portfolio portfolio = Portfolio(full);


    int nRuns = 20;
    vector<double> times = vector<double>(nRuns) ;

    for (int n = 0; n < nRuns; n++) {
        
        int nTargetReturns = 21;
        double step = 0.005;

        cout << "Target Return,\t IS Return,\t IS Std,\t OOS Return,\t OOS Std" << endl;
        for (int i = 0; i < nTargetReturns; i++) {
            double targetRet = i * step;
            Results results = portfolio.backtest(targetRet);
            cout << targetRet << ",\t " << results.retIS << ",\t " << results.stdIS
                 << ",\t " << results.retOOS << ",\t " << results.stdOOS << endl;
        }

        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        cout << "Time difference = " << chrono::duration_cast<chrono::seconds>(end - begin).count() << "[s]" << endl;
        double timeTaken = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
        cout << "Time difference = " << timeTaken << "[ms]"
             << endl;

        times[n] = timeTaken;
    }

    cout << "Mean of " << nRuns << " runs: " <<ParameterEstimator::calculateMean(&times) << " ms" << endl;
    cout << "Std of " << nRuns << " runs: " <<ParameterEstimator::calculateStd(&times) << " ms" << endl;




    return 0;
}

