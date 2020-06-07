
#include <numeric>
#include <cmath>
#include "PortfolioOptimiser.h"
#include "../util/VectorUtil.h"

using namespace std;

vector<double> PortfolioOptimiser::calculateWeights
        (Matrix *covariances, vector<double> *meanReturns) {

    vector<double> X0 = calculateX0();

    Matrix Q = this->generateQ(covariances, meanReturns);

    vector<double> B = this->generateB();

    vector<double> something = this->conjugateGradientMethod(&Q, &X0, &B);

    return something;
}

vector<double> PortfolioOptimiser::conjugateGradientMethod(Matrix *Q,
                                                           vector<double> *X0,
                                                           vector<double> *B) {
    vector<double> QX0 = Q->multiplyVector(X0);
    vector<double> sK = vectorSubtract(B, &QX0);

    double sumSquaredError = innerProduct(&sK, &sK);

    vector<double> pK = sK;
    vector<double> xK = *X0;

    int counter = 0;
    while (sumSquaredError > EPSILON) {

        vector<double> qPK = Q->multiplyVector(&pK);

        double alpha = sumSquaredError / innerProduct(&pK, &qPK);

        xK = vectorAdditions(1.0, &xK, alpha, &pK);
        sK = vectorAdditions(1.0, &sK, -alpha, &qPK);

        double newSumSquaredError = innerProduct(&sK, &sK);

        if (newSumSquaredError < EPSILON) break;

        double beta = newSumSquaredError / sumSquaredError;

        pK = vectorAdditions(1.0, &sK, beta, &pK);

        sumSquaredError = newSumSquaredError;
        counter++;
        if (counter == Q->getNRows() + 1) {
            cout << "Something has gone wrong, conjugate gradient should've converged by now.." << endl;
            cout << "\t Error: " << sumSquaredError << endl;
            exit(1);
        }
    }
    return vector<double>(xK.begin(), xK.end() - 2);
}

vector<double> PortfolioOptimiser::generateB() const {

    vector<double> b = vector<double>(nAssets + 2);
    for (int i = 0; i < nAssets; i++) {
        b[i] = 0.0;
    } // not necessary but maybe i havent initialised the first nAssets elements
    b[nAssets] = -targetReturn;
    b[nAssets + 1] = -1;
    return b;
}

Matrix PortfolioOptimiser::generateQ(Matrix *covariances, vector<double> *meanReturns) const {

    Matrix q = Matrix(nAssets + 2, nAssets + 2);

    for (int i = 0; i < nAssets; i++) {
        for (int j = 0; j < nAssets; j++) {
            q.set(i, j, covariances->get(i, j));
        }
    }

    for (int j = 0; j < nAssets; j++) {
        double thisMeanReturn = meanReturns->at(j);

        q.set(j, nAssets, -thisMeanReturn);
        q.set(j, nAssets + 1, -1);
        q.set(nAssets, j, -thisMeanReturn);
        q.set(nAssets + 1, j, -1);
    }
    return q;
}


vector<double> PortfolioOptimiser::calculateX0() {

    vector<double> x0 = vector<double>(nAssets + 2);
    for (int i = 0; i < nAssets; i++) {
        // initialising weights
        // first guess is an equally weighted optimiser
        x0[i] = 1.0 / nAssets;
    }
    x0[nAssets] = initialLambda;
    x0[nAssets + 1] = initialMu;

    return x0;
}


//    Matrix test = Matrix(4, 4);
//
//    test.set(0, 0, 1);
//    test.set(0, 1, 1);
//    test.set(0, 2, 1);
//    test.set(0, 3, 1);
//
//    test.set(1, 0, 2);
//    test.set(1, 1, 2);
//    test.set(1, 2, 2);
//    test.set(1, 3, 2);
//
//    test.set(2, 0, 3);
//    test.set(2, 1, 3);
//    test.set(2, 2, 3);
//    test.set(2, 3, 3);
//
//    test.set(3, 0, 4);
//    test.set(3, 1, 4);
//    test.set(3, 2, 4);
//    test.set(3, 3, 4);
//
//    vector<double> sK;
//    sK.push_back(2);
//    sK.push_back(3);
//    sK.push_back(4);
//    sK.push_back(5);


