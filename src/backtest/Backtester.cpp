#include "Backtester.h"
#include <iostream>
#include <cmath>
#include <vector>

Backtester::Backtester(RunConfig config_) {
    config = config_;
    all_returns = Matrix(config_.nDays, config_.nAssets);

    DataRepository(config_.fileName).readData(&all_returns);
    estimator = ParameterEstimator();

    optimiser = PortfolioOptimiser(config_.EPSILON,
                                   config_.initialLambda,
                                   config_.initialMu,
                                   config_.nAssets,
                                   config_.nDays);
    portfolio = Portfolio();
}

int Backtester::run(double dailyReturn) {
    // assets is columns, rows are days: C_ij = ith asset, jth day

    optimiser.setTargetDailyReturn(dailyReturn);

    int bWindowLength = 100; //days
    int tWindowLength = 12; //days

    int bTestStart = 100;
    int bTestEnd = config.nDays;

    for (int day = bTestStart; day < config.nDays; day += 100) {

        Matrix firstWindow = all_returns.get(
                day,
                bTestStart + bWindowLength,
                0,
                config.nAssets);

        vector<double> meanReturns = estimator.estimateMeanReturns(&firstWindow);

        Matrix cov = estimator.estimateCovariances(&firstWindow, &meanReturns);

        vector<double> portfolioWeights = optimiser.calculateWeights(&cov, &meanReturns);

        print(&portfolioWeights);

        portfolio.addWeightsToHistory(portfolioWeights);
        cout << "done" << endl;

        exit(42);
    }

    return 0;
}