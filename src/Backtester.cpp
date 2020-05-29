#include "Backtester.h"
#include "util/Matrix.h"
#include "DataRepository.h"
#include "ParameterEstimator.h"
#include <iostream>
#include <algorithm> // for copy
#include <iterator> // for ostream_iterator
#include <vector>

int Backtester::run(string filename, int nAssets, int nDays) {
    // assets is columns, rows are days: C_ij = ith asseth, jth day
    Matrix all_returns = Matrix(nDays, nAssets);

    DataRepository(filename, nAssets, nDays).readData(&all_returns);
    ParameterEstimator estimator = ParameterEstimator();

    int bWindowLength = 5; //days
    int tWindowLength = 2; //days

    int bTestStart = 0;
    int bTestEnd = nDays;
//    std::copy(col.begin(), col.end(), std::ostream_iterator<char>(cout, " "));

    for (int day = 0; day < bTestEnd; day++) {

        Matrix firstWindow = all_returns.get(
                bTestStart,
                bTestStart + bWindowLength,
                0,
                nAssets);

        vector<double> meanReturns = estimator.estimateMeanReturns(&firstWindow);

        Matrix test = Matrix(4, 3);

        test.set(0, 0, 45);
        test.set(0, 1, 37);
        test.set(0, 2, 42);

        test.set(1, 0, 38);
        test.set(1, 1, 31);
        test.set(1, 2, 26);

        test.set(2, 0, 10);
        test.set(2, 1, 15);
        test.set(2, 2, 17);

        test.set(3, 0, 1);
        test.set(3, 1, 2);
        test.set(3, 2, 3);

        vector<double> fake = estimator.estimateMeanReturns(&test);

        for(double elem:fake){
            cout<<elem<<endl;
        }

        Matrix cov = estimator.estimateCovariances(&test, &fake);

        cov.print();
        exit(1);

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

    return 0;
}