#ifndef MARKOWITZPORTFOLIOOPTIMISER_PORTFOLIOOPTIMISER_H
#define MARKOWITZPORTFOLIOOPTIMISER_PORTFOLIOOPTIMISER_H

#include <vector>
#include "../util/Matrix.h"

class PortfolioOptimiser {
private:
    double EPSILON;
    double initialLambda;
    double initialMu;
    double targetReturn{};
    int nAssets;

    vector<double> calculateX0();

    vector<double> generateB() const;

    Matrix generateQ(Matrix *covariances, vector<double> *meanReturns) const;

    vector<double> conjugateGradientMethod(Matrix *Q, vector<double> *X0, vector<double> *B);


public:
    PortfolioOptimiser(double epsilon_, double initialLambda_, double initialMu_, int nAssets_) {
        EPSILON = epsilon_;
        initialLambda = initialLambda_;
        initialMu = initialMu_;
        nAssets = nAssets_;
    }

    void setTargetDailyReturn(double portfolioReturn_) {
        targetReturn = portfolioReturn_;
    }

    vector<double> calculateWeights(Matrix *covariances,
                                    vector<double> *meanReturns);

};

#endif //MARKOWITZPORTFOLIOOPTIMISER_PORTFOLIOOPTIMISER_H
