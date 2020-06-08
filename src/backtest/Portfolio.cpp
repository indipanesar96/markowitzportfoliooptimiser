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

Results Portfolio::backtest(double dailyReturn) {
    // assets is columns, rows are days: C_ij = ith asset, jth day
    //        first window
    //        this->balance(returns[0:99])
    //        this->backtest(returns[100:111])
    //
    //        second window
    //        this->balance(returns[12:111])
    //        this->backtest(returns[112:123])

    optimiser.setTargetDailyReturn(dailyReturn);

    vector<double> portReturnsOOS = vector<double>(nWindows);
    vector<double> portReturnsIS = vector<double>(nWindows);

    int currentWindow = 0;
    for (int day = 0;
         day + config.bWindowLength + config.tWindowLength - 1 < config.nDays;
         day += 12) {

        int bStart = day;
        int bEnd = day + config.bWindowLength; // end not inclusive
        int tStart = day + config.bWindowLength;
        int tEnd = day + config.bWindowLength + config.tWindowLength; // end not inclusive

        Matrix balanceWindow = allReturns.getAllCols(bStart, bEnd);
        Matrix testWindow = allReturns.getAllCols(tStart, tEnd);

        vector<double> portfolioWeights = this->balance(&balanceWindow);

        portReturnsOOS[currentWindow] = Portfolio::evaluate(&testWindow, &portfolioWeights);
        portReturnsIS[currentWindow] = Portfolio::evaluate(&balanceWindow, &portfolioWeights);

        currentWindow += 1;
    }

    return (Results) {
            ParameterEstimator::calculateMean(&portReturnsOOS), //Mean of portfolio Return across all windows, Out Of Sample
            ParameterEstimator::calculateMean(&portReturnsIS), //Mean of portfolio Return across all windows, In Sample
            ParameterEstimator::calculateStd(&portReturnsOOS), //Std of portfolio Return across all windows, Out Of Sample
            ParameterEstimator::calculateStd(&portReturnsIS) //Std of portfolio Return across all windows, In Sample
    };
}

double Portfolio::evaluate(Matrix *m, vector<double> *weights) {

    vector<double> aveAssetReturns = ParameterEstimator::estimateMultipleMeans(m);

    return innerProduct(&aveAssetReturns, weights);
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