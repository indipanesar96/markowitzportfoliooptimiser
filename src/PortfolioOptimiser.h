#ifndef MARKOWITZPORTFOLIOOPTIMISER_PORTFOLIOOPTIMISER_H
#define MARKOWITZPORTFOLIOOPTIMISER_PORTFOLIOOPTIMISER_H

#include <vector>
#include "util/Matrix.h"

class PortfolioOptimiser {
    double epsilon;
    double initialLambda;
    double initialMu;

    vector<double> calculateX0(Matrix *returns, int nAssets) const;
    static Matrix calculateQ(Matrix *covariances, vector<double> *meanReturns, int nAssets);

public:
    PortfolioOptimiser(double epsilon_,
                       double initialLambda_,
                       double initialMu_) {
        epsilon = epsilon_;
        initialLambda = initialLambda_;
        initialMu = initialMu_;
    }

    vector<double> calculateWeights(Matrix *covariances,
                                    vector<double> *meanReturns);


};

#endif //MARKOWITZPORTFOLIOOPTIMISER_PORTFOLIOOPTIMISER_H
