#include "Backtester.h"
#include "util/Matrix.h"
#include "DataRepository.h"
#include "PortfolioOptimiser.h"
#include "ParameterEstimator.h"
#include "Portfolio.h"
#include <iostream>
#include <cmath>
#include <vector>

int Backtester::run(string filename, int nAssets, int nDays) {
    // assets is columns, rows are days: C_ij = ith asseth, jth day
    Matrix all_returns = Matrix(nDays, nAssets);

    DataRepository(filename, nAssets, nDays).readData(&all_returns);
    ParameterEstimator estimator = ParameterEstimator();
    PortfolioOptimiser optimiser = PortfolioOptimiser(pow(10, -6), 0.5, 0.5, all_returns.getNCols());
    Portfolio portfolio = Portfolio();

    // for initial testing, ideally we should pass this in from main
    double dailyReturn = 0.0001;
    optimiser.setTargetDailyReturn(dailyReturn);

    int bWindowLength = 5; //days
    int tWindowLength = 2; //days

    int bTestStart = 0;
    int bTestEnd = nDays;
//    std::copy(col.begin(), col.end(), std::ostream_iterator<char>(cout, " "));
    int day=0;
    while (day < bTestEnd){

        Matrix firstWindow = all_returns.get(
                bTestStart,
                bTestStart + bWindowLength,
                0,
                nAssets);

        vector<double> meanReturns = estimator.estimateMeanReturns(&firstWindow);

        Matrix cov = estimator.estimateCovariances(&firstWindow, &meanReturns);

        vector<double> portfolioWeights = optimiser.calculateWeights(&cov, &meanReturns);

        cout <<"backltester"<<endl;
        print(&portfolioWeights);

        portfolio.addWeightsToHistory(portfolioWeights);



        exit(1);
        day++;
    }

    return 0;
}