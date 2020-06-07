
#ifndef MARKOWITZPORTFOLIOOPTIMISER_PARAMETERESTIMATOR_H
#define MARKOWITZPORTFOLIOOPTIMISER_PARAMETERESTIMATOR_H

#include<vector>
#include"../util/Matrix.h"

class ParameterEstimator {
public:

    static vector<double> estimateMultipleMeans(Matrix *m);

    static Matrix estimateCovariances(Matrix *m, vector<double> *meanReturns);

    static double calculateStd(vector<double> *vals);

    static double calculateMean(vector<double> *values);
};

#endif //MARKOWITZPORTFOLIOOPTIMISER_PARAMETERESTIMATOR_H
