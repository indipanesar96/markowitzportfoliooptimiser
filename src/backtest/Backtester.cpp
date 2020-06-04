#include "Backtester.h"
#include "../util/Matrix.h"
#include "../util/RunConfig.h"
#include "../repository/DataRepository.h"
#include "../portfolio/PortfolioOptimiser.h"
#include "../parameterestimator/ParameterEstimator.h"
#include "../portfolio/Portfolio.h"
#include <iostream>
#include <cmath>
#include <vector>

int Backtester::run(RunConfig config) {
    // assets is columns, rows are days: C_ij = ith asseth, jth day

    Matrix all_returns = Matrix(config.nDays, config.nAssets);

    DataRepository(config.fileName).readData(&all_returns);
    ParameterEstimator estimator = ParameterEstimator();

    PortfolioOptimiser optimiser = PortfolioOptimiser(config.EPSILON,
                                                      config.initialLambda,
                                                      config.initialMu,
                                                      config.nAssets);
    Portfolio portfolio = Portfolio();

    // for initial testing, ideally we should pass this in from main
    double dailyReturn = 0.0001;
    optimiser.setTargetDailyReturn(dailyReturn);

    int bWindowLength = 5; //days
    int tWindowLength = 2; //days

    int bTestStart = 100;
    int bTestEnd = config.nDays;
//    std::copy(col.begin(), col.end(), std::ostream_iterator<char>(cout, " "));
    int day = 0;
    while (day < bTestEnd) {

        Matrix firstWindow = all_returns.get(
                bTestStart,
                bTestStart + bWindowLength,
                0,
                config.nAssets);

        vector<double> meanReturns = estimator.estimateMeanReturns(&firstWindow);

        Matrix cov = estimator.estimateCovariances(&firstWindow, &meanReturns);

        vector<double> portfolioWeights = optimiser.calculateWeights(&cov, &meanReturns);

        cout << "backtester" << endl;
        print(&portfolioWeights);

        portfolio.addWeightsToHistory(portfolioWeights);


        exit(1);
        day++;
    }

    return 0;
}