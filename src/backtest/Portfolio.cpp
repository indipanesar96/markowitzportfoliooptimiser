#include "Portfolio.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
#include "../util/VectorUtil.h"

using namespace std;

Portfolio::Portfolio(RunConfig config_) {
    config = config_;
    allReturns = Matrix(config_.nDays, config_.nAssets);

    DataRepository(config_.fileName, config_.nAssets).readData(&allReturns);

    nWindows = (config.nDays - config.bWindowLength) / config.tWindowLength;

    optimiser = PortfolioOptimiser(config_.EPSILON,
                                   config_.initialLambda,
                                   config_.initialMu,
                                   config_.nAssets);
}

BacktestResults Portfolio::backtest(double dailyReturn) {
    // assets is columns, rows are days: C_ij = ith asset, jth day
    optimiser.setTargetDailyReturn(dailyReturn);

    vector<double> portReturnsOOS = vector<double>(nWindows);
    vector<double> portCovarianceOOS = vector<double>(nWindows);

    vector<double> portReturnsIS = vector<double>(nWindows);
    vector<double> portCovarianceIS = vector<double>(nWindows);

    int currentWindow = 0;
    double nShorts = 0;

    for (int day = 0;
         day + config.bWindowLength + config.tWindowLength <= config.nDays;
         day += 12) {

        int bStart = day;
        int bEnd = day + config.bWindowLength; // end not inclusive
        int tStart = day + config.bWindowLength;
        int tEnd = day + config.bWindowLength + config.tWindowLength; // end not inclusive

        Matrix balanceWindow = allReturns.getAllCols(bStart, bEnd);
        Matrix testWindow = allReturns.getAllCols(tStart, tEnd);

        vector<double> portfolioWeights = this->balance(&balanceWindow);

        Portfolio::evaluate(&balanceWindow, &portfolioWeights, &portReturnsIS, &portCovarianceIS, currentWindow);
        Portfolio::evaluate(&testWindow, &portfolioWeights, &portReturnsOOS, &portCovarianceOOS, currentWindow);

        nShorts += countNegative(portfolioWeights) / nWindows;

        currentWindow += 1;
    }

    //    cout << "(Average Number of Shorts, Target Return): " << nShorts << ", " << dailyReturn <<endl;

    // returning the means and variances of portfolio return across all windows, Out Of Sample & In sample
    return (BacktestResults) {
            ParameterEstimator::calculateMean(&portReturnsOOS),
            ParameterEstimator::calculateMean(&portReturnsIS),
            ParameterEstimator::calculateMean(&portCovarianceOOS),
            ParameterEstimator::calculateMean(&portCovarianceIS)
    };
}


void Portfolio::evaluate(
        Matrix *m,
        vector<double> *weights,
        vector<double> *returnsVector,
        vector<double> *covariancesVector,
        int index
) {

    vector<double> aveAssetReturns = ParameterEstimator::estimateMultipleMeans(m);

    Matrix cov = ParameterEstimator::estimateCovariances(m, &aveAssetReturns);
    vector<double> sigmaW = cov.multiplyVector(weights); // Sigma * w

    returnsVector->at(index) = innerProduct(&aveAssetReturns, weights);
    covariancesVector->at(index) = innerProduct(weights, &sigmaW); // w' * Sigma * w
}


vector<double> Portfolio::balance(Matrix *m) {
    vector<double> meanReturns = ParameterEstimator::estimateMultipleMeans(m);

    Matrix cov = ParameterEstimator::estimateCovariances(m, &meanReturns);

    vector<double> weights = optimiser.calculateWeights(&cov, &meanReturns);
    this->checkWeights(weights);
    return weights;

}

void Portfolio::checkWeights(vector<double> &w) const {

    double sum = accumulate(w.begin(), w.end(), 0.0);

    if (abs(sum - 1.0) > config.WEIGHTSTOLERANCE) {
        cout << "The sum of the weights is: " << sum << endl;
        cout << "Exiting as weights are incorrect" << endl;
        exit(42);
    }

}