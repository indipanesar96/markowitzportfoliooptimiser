#include "Backtester.h"
#include "util/Matrix.h"
#include "DataRepository.h"
#include "PortfolioOptimiser.h"
#include "ParameterEstimator.h"
#include <iostream>
#include <algorithm> // for copy
#include <iterator> // for ostream_iterator
#include <vector>

int Backtester::run(string filename, int nAssets, int nDays) {
    // assets is columns, rows are days: C_ij = ith asseth, jth day
    Matrix all_returns = Matrix(nDays, nAssets);

    DataRepository(filename, nAssets, nDays).readData(&all_returns);
    ParameterEstimator estimator = ParameterEstimator();
    PortfolioOptimiser optimiser = PortfolioOptimiser(0.000001, 0.5, 0.5);

    int bWindowLength = 5; //days
    int tWindowLength = 2; //days

    int bTestStart = 0;
    int bTestEnd = nDays;
//    std::copy(col.begin(), col.end(), std::ostream_iterator<char>(cout, " "));

    for (int day = 0; day < bTestEnd; day++) {

        Matrix firstWindow = all_returns.get(
                bTestStart,
                bTestStart + bWindowLength,
                0,
                nAssets);

        vector<double> meanReturns = estimator.estimateMeanReturns(&firstWindow);

        Matrix cov = estimator.estimateCovariances(&firstWindow, &meanReturns);

        cov.print();
        vector<double> portfolioWeights = optimiser.calculateWeights(&cov, &meanReturns);

        exit(1);

    }

    return 0;
}