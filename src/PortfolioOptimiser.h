#ifndef MARKOWITZPORTFOLIOOPTIMISER_PORTFOLIOOPTIMISER_H
#define MARKOWITZPORTFOLIOOPTIMISER_PORTFOLIOOPTIMISER_H

#include <vector>
#include "util/Matrix.h"

class PortfolioOptimiser {
private:
    double epsilon;
    double initialLambda;
    double initialMu;
    double portfolioReturn{};
    int nAssets;

    vector<double> calculateX0() const;

    vector<double> calculateB() const;

    Matrix calculateQ(Matrix *covariances, vector<double> *meanReturns) const;

    vector<double> conjugateGradientMethod(Matrix *Q, vector<double> *X0, vector<double> *B) const;


public:
    PortfolioOptimiser(double epsilon_,
                       double initialLambda_,
                       double initialMu_,
                       int nAssets_) {
        epsilon = epsilon_;
        initialLambda = initialLambda_;
        initialMu = initialMu_;
        nAssets = nAssets_;
    }

    void setRequiredPortfolioReturn(double portfolioReturn_) {
        portfolioReturn = portfolioReturn_;
    }

    vector<double> calculateWeights(Matrix *covariances,
                                    vector<double> *meanReturns);

};

#endif //MARKOWITZPORTFOLIOOPTIMISER_PORTFOLIOOPTIMISER_H
