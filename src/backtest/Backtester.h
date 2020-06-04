
#ifndef MARKOWITZPORTFOLIOOPTIMISER_BACKTESTER_H
#define MARKOWITZPORTFOLIOOPTIMISER_BACKTESTER_H

#include "../util/RunConfig.h"
#include "../util/Matrix.h"
#include "../repository/DataRepository.h"
#include "../portfolio/PortfolioOptimiser.h"
#include "../parameterestimator/ParameterEstimator.h"
#include "../portfolio/Portfolio.h"

using namespace std;

class Backtester {

public:
    int run(double dailyReturn);

    explicit Backtester(RunConfig config_);

    Matrix all_returns = Matrix(1, 1);
    RunConfig config = RunConfig(0.5, 0.5, 1, 1, "");
    ParameterEstimator estimator = ParameterEstimator();
    PortfolioOptimiser optimiser = PortfolioOptimiser(1, 1, 1, 1, 1);
    Portfolio portfolio = Portfolio();

    // default vals
};


#endif