
#include "ParameterEstimator.h"
#include <numeric>

vector<double> ParameterEstimator::estimateMeanReturns(Matrix *m) {

    int nCols = m->getNCols();
    int nRows = m->getNRows();
    vector<double> means = vector<double>(nCols);

    for (int i = 0; i < nCols; i++) {
        vector<double> column = m->getCol(i);
        double sum = accumulate(column.begin(), column.end(), 0.0);
        means[i] = sum / nRows;
    }

    return means;
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
                double d = m->get(day, a1) - a1mean;
                double d1 = m->get(day, a2) - a2mean;
                temp += d * d1;
            }
            covariances.set(a1, a2, (temp / (nDays - 1)));
        }
    }

    return covariances;
}
