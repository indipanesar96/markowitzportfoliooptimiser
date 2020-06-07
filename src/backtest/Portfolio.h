
#ifndef MARKOWITZPORTFOLIOOPTIMISER_PORTFOLIO_H
#define MARKOWITZPORTFOLIOOPTIMISER_PORTFOLIO_H

#include "../util/RunConfig.h"
#include "../util/Matrix.h"
#include "../util/Results.h"
#include "../repository/DataRepository.h"
#include "../optimiser/PortfolioOptimiser.h"
#include "../estimator/ParameterEstimator.h"
#include "../optimiser/PortfolioOptimiser.h"
#include <vector>

using namespace std;

class Portfolio {
private:
    vector<vector<double>> weightsHistory;

    vector<double> balance(Matrix *m);

    double evaluate(Matrix *m, vector<double> *weights) const;

    void checkWeights(vector<double> &w) const;

    void addWeightsToHistory(vector<double> &weights);


public:
    Results backtest(double dailyReturn);

    explicit Portfolio(RunConfig config_);

    // default vals
    Matrix allReturns = Matrix(4, 2);
    RunConfig config = RunConfig{0.5, 0.5, 1, 1, 2, 1, ""};
    PortfolioOptimiser optimiser = PortfolioOptimiser(1, 1, 1, 1);
    int nWindows = (config.nDays - config.bWindowLength) / config.tWindowLength;
};


#endif