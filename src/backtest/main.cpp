#include "Portfolio.cpp"
#include <chrono>

using namespace std;

void multipleRuns(int nRuns, vector<double> assets, RunConfig config);

int main(int argc, char *argv[]) {

    // RunConfigs I used for testing/building the app
//    RunConfig small = RunConfig{0.5,
//                                0.5,
//                                9,
//                                2,
//                                2,
//                                1,
//                                "../resources/test_asset_returns.csv"};
//    RunConfig medium = RunConfig{0.5,
//                                 0.5,
//                                 50,
//                                 4,
//                                 5,
//                                 2,
//                                 "../resources/medium_asset_returns.csv"};
    RunConfig full = RunConfig(0.5,
                               0.5,
                               700,
                               83,
                               12,
                               100,
                               "../resources/asset_returns.csv");


    int nRuns = 1;
    // Below is the testing for the time complexity analysis
//    vector<double> assets = vector<double>{2, 5, 8, 16, 32, 64};
    vector<double> assets = vector<double>{83, 83, 83, 83, 83, 83}; // size must be same as nRuns above

    multipleRuns(nRuns, assets, full);


    return 0;
}

void multipleRuns(int nRuns, vector<double> assets, RunConfig config) {
    // run the application multiple times, for time complexity
    // analysis and to generate timings for performance anlysis


    int nPortfolios = 21; // 21 portfolios from 0% to 10% target returns
    double step = 0.005; // each portfolio target return goes up by 0.5%
    vector<double> times = vector<double>(nRuns);
    int nWindows = (config.nDays - config.bWindowLength) / config.tWindowLength  ;

    for (int n = 0; n < nRuns; n++) {
        chrono::steady_clock::time_point begin = chrono::steady_clock::now();

        // change the number of assets to be used for this iteration
        config.setNAssets(assets[n]);

        Matrix allRealisedPortReturnsOOS = Matrix(nWindows, nPortfolios);
        Matrix allRealisedMktReturnsOOS = Matrix(nWindows, nPortfolios);

        Portfolio portfolio = Portfolio(config, &allRealisedPortReturnsOOS, &allRealisedMktReturnsOOS);

        cout << "Target Return,\t IS Return,\t IS Var,\t OOS Return,\t OOS Var, \t nAssets: " << assets[n] << endl;
        for (int p = 0; p < nPortfolios; p++) {

            double targetRet = p * step;
            BacktestResults results = portfolio.backtest(targetRet, p);
            cout << targetRet << ",\t " << results.retIS << ",\t " << results.varIS
                 << ",\t " << results.retOOS << ",\t " << results.varOOS << endl;
        }
//        allRealisedPortReturnsOOS.print();
//        cout<<endl;
//        allRealisedMktReturnsOOS.print();

        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        double timeTaken = chrono::duration_cast<chrono::milliseconds>(end - begin).count();

        cout << "Time taken: " << timeTaken << "[ms]" << endl;
        cout << endl;
        times[n] = timeTaken;
    }

    cout << "Mean of " << nRuns << " runs: " << ParameterEstimator::calculateMean(&times) << " ms" << endl;
    cout << "Std of " << nRuns << " runs: " << ParameterEstimator::calculateStd(&times) << " ms" << endl;

    cout << "Times:" << endl;
    printVector(&times);
}