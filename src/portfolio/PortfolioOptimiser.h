#ifndef MARKOWITZPORTFOLIOOPTIMISER_PORTFOLIOOPTIMISER_H
#define MARKOWITZPORTFOLIOOPTIMISER_PORTFOLIOOPTIMISER_H

#include <vector>
#include "../util/Matrix.h"

class PortfolioOptimiser {
private:
    double EPSILON;
    double initialLambda;
    double initialMu;
    double portfolioReturn{};
    int nAssets;
    int nDays;

    vector<double> calculateX0();

    vector<double> generateB();

    Matrix generateQ(Matrix *covariances, vector<double> *meanReturns);

    vector<double> conjugateGradientMethod(Matrix *Q, vector<double> *X0, vector<double> *B);


public:
    PortfolioOptimiser(double epsilon_,
                       double initialLambda_,
                       double initialMu_,
                       int nAssets_,
                       int nDays_) {
        EPSILON = epsilon_;
        initialLambda = initialLambda_;
        initialMu = initialMu_;
        nAssets = nAssets_;
        nDays = nDays_;
    }

    void setTargetDailyReturn(double portfolioReturn_) {
        portfolioReturn = portfolioReturn_;
    }

    vector<double> calculateWeights(Matrix *covariances,
                                    vector<double> *meanReturns);

};

#endif //MARKOWITZPORTFOLIOOPTIMISER_PORTFOLIOOPTIMISER_H
