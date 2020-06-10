
#ifndef MARKOWITZPORTFOLIOOPTIMISER_PORTFOLIO_H
#define MARKOWITZPORTFOLIOOPTIMISER_PORTFOLIO_H

#include "../util/RunConfig.h"
#include "../util/Matrix.h"
#include "../util/BacktestResults.h"
#include "../repository/DataRepository.h"
#include "../optimiser/PortfolioOptimiser.h"
#include "../estimator/ParameterEstimator.h"
#include "../optimiser/PortfolioOptimiser.h"
#include <vector>

using namespace std;

class Portfolio {
private:
    vector<double> balance(Matrix *m);

    static void evaluate(
            Matrix *m,
            vector<double> *weights,
            vector<double> *returnsVector,
            vector<double> *covariancesVector,
            int index);

    void checkWeights(vector<double> &w) const;

public:
    BacktestResults backtest(double targetReturn);

    explicit Portfolio(RunConfig config_);

    // default vals
    Matrix allReturns = Matrix(4, 2);
    RunConfig config = RunConfig{0.5, 0.5, 1, 1, 2, 1, ""};
    PortfolioOptimiser optimiser = PortfolioOptimiser(1, 1, 1, 1);
    int nWindows = (config.nDays - config.bWindowLength) / config.tWindowLength;
};

#endif