
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
                temp += (m->get(day, a1) - a1mean) * (m->get(day, a2) - a2mean);
            }
            covariances.set(a1, a2, (temp / (nDays - 1)));
        }
    }

    return covariances;
}
//    import numpy as np
//
//    A = [45,37,42]
//    B = [38,31,26]
//    C = [10,15,17]
//    D = [1,2,3]
//
//    data = np.array([A,B,C,D]).T
//
//    print(data)
//    print(np.mean(data, axis=0))
//
//    covMatrix = np.cov(data,bias=False)
//    print (covMatrix)


//Matrix test = Matrix(4, 3);
//
//vector<double> fake = estimator.estimateMeanReturns(&test);
//
//test.set(0, 0, 45);
//test.set(0, 1, 37);
//test.set(0, 2, 42);
//
//test.set(1, 0, 38);
//test.set(1, 1, 31);
//test.set(1, 2, 26);
//
//test.set(2, 0, 10);
//test.set(2, 1, 15);
//test.set(2, 2, 17);
//
//test.set(3, 0, 1);
//test.set(3, 1, 2);
//test.set(3, 2, 3);