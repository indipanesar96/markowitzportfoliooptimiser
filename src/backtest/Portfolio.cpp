#include "Portfolio.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
#include "../util/VectorUtil.h"

using namespace std;

Portfolio::Portfolio(RunConfig config_, Matrix* allPortReturns_, Matrix* allMktReturns_){

    config = config_;
    nWindows = (config_.nDays - config_.bWindowLength) / config_.tWindowLength;

    // matrices to store portfolio and market returns to track
    // their evolution over multiple runs with different targets
    allOOSPortReturns = allPortReturns_ ;
    allMktOOSReturns = allMktReturns_;

    // pass through values from our RunConfig to initialise our optimiser
    optimiser = PortfolioOptimiser(config_.EPSILON,
                                   config_.initialLambda,
                                   config_.initialMu,
                                   config_.nAssets);

    equallyWeightPortfolio = vector<double>(config_.nAssets);
    for (int i=0; i<config.nAssets; i++){
        equallyWeightPortfolio[i] = 1.0 / config.nAssets;
    }

    allReturns = Matrix(config_.nDays, config_.nAssets);

    // load data inside here
    DataRepository(config_.fileName, config_.nAssets).readData(&allReturns);
}

BacktestResults Portfolio::backtest(double targetReturn, int runNumber) {

    // assets is columns, rows are days: C_ij = ith asset, jth day
    // using the setter to change the target return every time
    optimiser.setTargetReturn(targetReturn);

    vector<double> portReturnsOOS = vector<double>(nWindows);
    vector<double> portCovarianceOOS = vector<double>(nWindows);

    vector<double> portReturnsIS = vector<double>(nWindows);
    vector<double> portCovarianceIS = vector<double>(nWindows);

    vector<double> mktReturnsIS = vector<double>(nWindows);
    vector<double> mktCovarianceIS = vector<double>(nWindows);

    vector<double> mktReturnsOOS = vector<double>(nWindows);
    vector<double> mktCovarianceOOS = vector<double>(nWindows);

    int currentWindow = 0;
    double nShorts = 0;

    for (int day = 0;
         day + config.bWindowLength + config.tWindowLength <= config.nDays;
         day += 12) {

        int bStart = day;
        int bEnd = day + config.bWindowLength; // end not inclusive
        int tStart = day + config.bWindowLength;
        int tEnd = day + config.bWindowLength + config.tWindowLength; // end not inclusive

        // splicing all returns into in and out of sample windows
        Matrix balanceWindow = allReturns.getAllCols(bStart, bEnd);
        Matrix testWindow = allReturns.getAllCols(tStart, tEnd);

        vector<double> portfolioWeights = this->balance(&balanceWindow);

        Portfolio::evaluate(&balanceWindow, &portfolioWeights, &portReturnsIS, &portCovarianceIS, currentWindow);
        Portfolio::evaluate(&testWindow, &portfolioWeights, &portReturnsOOS, &portCovarianceOOS, currentWindow);

        Portfolio::evaluate(&balanceWindow, &equallyWeightPortfolio, &mktReturnsIS, &mktCovarianceIS, currentWindow);
        Portfolio::evaluate(&testWindow, &equallyWeightPortfolio, &mktReturnsOOS, &mktCovarianceOOS, currentWindow);

        nShorts += countNegative(portfolioWeights) / nWindows;


        currentWindow += 1;
    }

    allOOSPortReturns->setCol(runNumber, &portReturnsOOS);
    allMktOOSReturns->setCol(runNumber, &mktReturnsOOS);

    // below is the output required for the time complexity analysis
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
    // function used to evaluate the performance of our portfolio with weights from QCM
    // Calculate mean returns and variance of the portfolio

    vector<double> aveAssetReturns = ParameterEstimator::estimateMultipleMeans(m);
    returnsVector->at(index) = innerProduct(&aveAssetReturns, weights);

    Matrix cov = ParameterEstimator::estimateCovariances(m, &aveAssetReturns);
    vector<double> sigmaW = cov.multiplyVector(weights); // Sigma * w
    covariancesVector->at(index) = innerProduct(weights, &sigmaW); // w' * Sigma * w
}


vector<double> Portfolio::balance(Matrix *m) {
    // function used to generate weights by wrapping the call to
    // optimiser.calculateWeights

    vector<double> meanReturns = ParameterEstimator::estimateMultipleMeans(m);
    Matrix cov = ParameterEstimator::estimateCovariances(m, &meanReturns);
    vector<double> weights = optimiser.calculateWeights(&cov, &meanReturns);
    this->checkWeights(weights);

    return weights;

}

void Portfolio::checkWeights(vector<double> &w) const {
    // a vital check to ensure that our weights summed to unity to within a tolerance

    double sum = accumulate(w.begin(), w.end(), 0.0);

    if (abs(sum - 1.0) > config.WEIGHTSTOLERANCE) {
        cout << "The sum of the weights is: " << sum << endl;
        cout << "Exiting as weights are incorrect" << endl;
        exit(42);
    }

}