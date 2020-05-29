
#ifndef MARKOWITZPORTFOLIOOPTIMISER_PARAMETERESTIMATOR_H
#define MARKOWITZPORTFOLIOOPTIMISER_PARAMETERESTIMATOR_H
#include<vector>
#include"util/Matrix.h"

class ParameterEstimator{
public:

    vector<double> estimateMeanReturns(Matrix* m);
    Matrix estimateCovariances(Matrix* m, vector<double>* meanReturns);
};

#endif //MARKOWITZPORTFOLIOOPTIMISER_PARAMETERESTIMATOR_H
