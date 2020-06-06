
#ifndef MARKOWITZPORTFOLIOOPTIMISER_PORTFOLIO_H
#define MARKOWITZPORTFOLIOOPTIMISER_PORTFOLIO_H

#include "../util/RunConfig.h"
#include "../util/Matrix.h"
#include "../util/Results.h"
#include "../repository/DataRepository.h"
#include "../portfolio/PortfolioOptimiser.h"
#include "../parameterestimator/ParameterEstimator.h"
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
    Results run(double dailyReturn);

    explicit Portfolio(RunConfig config_);

    Matrix allReturns = Matrix(1, 1);
    RunConfig config = RunConfig(0.5, 0.5, 1, 1, -1, -1, "");
    PortfolioOptimiser optimiser = PortfolioOptimiser(1, 1, 1, 1, 1);
    int tWindowLength = 0;
    int bWindowLength = 0;
    double WEIGHTS_TOLERANCE = pow(10, -3);
    int nWindows = (config.nDays - config.bWindowLength) / config.tWindowLength;
    // default vals
};


#endif