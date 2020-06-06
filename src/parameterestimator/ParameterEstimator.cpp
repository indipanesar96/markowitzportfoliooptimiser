
#include "ParameterEstimator.h"
#include <numeric>
#include <cmath>

vector<double> ParameterEstimator::estimateMultipleMeans(Matrix *m) {

    int nCols = m->getNCols();
    vector<double> means = vector<double>(nCols);

    for (int i = 0; i < nCols; i++) {
        vector<double> column = m->getCol(i);
        means[i] = calculateMean(&column);
    }

    return means;
}

double ParameterEstimator::calculateMean(vector<double> *values) {
    return accumulate(values->begin(), values->end(), 0.0) / values->size();
}

double ParameterEstimator::calculateStd(vector<double> *vals) {

    int s = vals->size();
    double mean = calculateMean(vals);
    double var = 0.0;

    for (double elem: *vals) {
        var += pow((elem - mean), 2) / (s - 1);
    }

    return pow(var, 0.5);
}

Matrix ParameterEstimator::estimateCovariances
        (Matrix *m, vector<double> *meanReturns) {

    int nAssets = m->getNCols();
    int nDays = m->getNRows();

    Matrix covariances = Matrix(nAssets, nAssets);

    for (int a1 = 0; a1 < nAssets; a1++) {
        double a1mean = meanReturns->at(a1);

        for (int a2 = 0; a2 < nAssets; a2++) {
            double a2mean = meanReturns->at(a2);
            double temp = 0.0;

            for (int day = 0; day < nDays; day++) {
                temp += (m->get(day, a1) - a1mean) * (m->get(day, a2) - a2mean);
            }
            covariances.set(a1, a2, (temp / (nDays - 1)));
        }
    }

    return covariances;
}