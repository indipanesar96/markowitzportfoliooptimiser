#include "PortfolioOptimiser.h"

vector<double> PortfolioOptimiser::calculateWeights
        (Matrix *covariances, vector<double> *meanReturns) {

    int nAssets = covariances->getNCols();


    // 1: initialise x0
    vector<double> x0 = calculateX0();

    // 2. create Q (i+2 x i+2) matrix, i=num assets
    Matrix Q = calculateQ(covariances, meanReturns);
    Q.print();

    // 3. create b (static)
    vector<double> B = calculateB();



    // 4. run conjugate method

    //https://stackoverflow.com/questions/10908012/computing-the-scalar-product-of-two-vectors-in-c



    return vector<double>();
}

vector<double> PortfolioOptimiser::conjugateGradientMethod(Matrix* Q,
                                                          vector<double>* X0,
                                                          vector<double>* B) const {
    vector<double> product = Q->multiplyVector(X0);
    for (double elem: product) {
        cout << elem << endl;

    }
    // checker : https://matrix.reshish.com/multiplication.php


}


vector<double> PortfolioOptimiser::calculateB() const {

    vector<double> b = vector<double>(nAssets + 2);
    b[nAssets] = -portfolioReturn;
    b[nAssets + 1] = -1;
    return b;
}

Matrix PortfolioOptimiser::calculateQ(Matrix *covariances, vector<double> *meanReturns) const {

    Matrix q = Matrix(nAssets + 2, nAssets + 2);

    for (int i = 0; i < covariances->getNRows(); i++) {
        for (int j = 0; j < nAssets; j++) {
            q.set(i, j, covariances->get(i, j));
        }
    }

    for (int j = 0; j < nAssets; j++) {
        double thisMeanReturn = (*meanReturns)[j];

        q.set(j, nAssets, -thisMeanReturn);
        q.set(j, nAssets + 1, -1);
        q.set(nAssets, j, -thisMeanReturn);
        q.set(nAssets + 1, j, -1);
    }

    return q;
}


vector<double> PortfolioOptimiser::calculateX0() const {

    vector<double> x0 = vector<double>(nAssets + 2);
    for (int i = 0; i < nAssets; i++) {
        // initialising weights
        // first guess is an equally weighted portfolio
        x0[i] = 1.0 / nAssets;
    }
    x0[nAssets + 0] = initialLambda;
    x0[nAssets + 1] = initialMu;

    return x0;
}



