#include "Portfolio.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
#include "../util/VectorUtil.h"

using namespace std;

void Portfolio::addWeightsToHistory(vector<double> &weights) {
    this->weightsHistory.push_back(weights);
}

Portfolio::Portfolio(RunConfig config_) {
    config = config_;
    allReturns = Matrix(config_.nDays, config_.nAssets);

    DataRepository(config_.fileName).readData(&allReturns);
    estimator = ParameterEstimator();

    tWindowLength = config_.tWindowLength;
    bWindowLength = config_.bWindowLength;
    nWindows = (config.nDays - config.bWindowLength) / config.tWindowLength;

    optimiser = PortfolioOptimiser(config_.EPSILON,
                                   config_.initialLambda,
                                   config_.initialMu,
                                   config_.nAssets,
                                   config_.nDays);
}

double Portfolio::run(double dailyReturn) {
    // assets is columns, rows are days: C_ij = ith asset, jth day

    optimiser.setTargetDailyReturn(dailyReturn);

    vector<double> portReturnsOOS = vector<double>(nWindows);
    vector<double> portReturnsIS = vector<double>(nWindows);
    int currentWindow = 0;


    for (int day = 0; day + bWindowLength + tWindowLength - 1 < config.nDays; day += 12) {

        int bStart = day;
        int bEnd = day + bWindowLength; // end not inclusive
        int tStart = day + bWindowLength;
        int tEnd = day + bWindowLength + tWindowLength; // end not inclusive

        Matrix balanceWindow = allReturns.getAllCols(bStart, bEnd);
        Matrix testWindow = allReturns.getAllCols(tStart, tEnd);

        if (false) {
            cout << endl;
            cout << day << endl;
            cout << "bStart: " << bStart << " bEnd: " << bEnd << endl;
            cout << "tStart: " << tStart << " tEnd: " << tEnd << endl;
        }

        vector<double> portfolioWeights = this->balance(&balanceWindow);

        portReturnsOOS[currentWindow] = this->evaluate(&testWindow, &portfolioWeights);
        portReturnsIS[currentWindow] = this->evaluate(&balanceWindow, &portfolioWeights);

        currentWindow += 1;
    }

    double avePortReturn = accumulate(portReturnsOOS.begin(), portReturnsOOS.end(), 0.0) / nWindows;

    double avePortReturnInSample = accumulate(portReturnsIS.begin(), portReturnsIS.end(), 0.0) / nWindows;
    return avePortReturn;
}

double Portfolio::evaluate(Matrix *m, vector<double> *weights) {

    vector<double> aveAssetReturns = estimator.estimateMeanReturns(m);

    double portReturn = 0;
    for (int asset = 0; asset < config.nAssets; asset++) {
        portReturn += aveAssetReturns[asset] * weights->at(asset);
    }
    return portReturn;
}


vector<double> Portfolio::balance(Matrix *m) {
    vector<double> meanReturns = estimator.estimateMeanReturns(m);
    Matrix cov = estimator.estimateCovariances(m, &meanReturns);
    vector<double> weights = optimiser.calculateWeights(&cov, &meanReturns);
    this->checkWeights(weights);
    this->addWeightsToHistory(weights);
    return weights;

}

void Portfolio::checkWeights(vector<double> &w) const {

    double sum = accumulate(w.begin(), w.end(), 0.0);

    if (abs(sum - 1.0) > WEIGHTS_TOLERANCE) {
        cout << "The sum of the weights is: " << sum << endl;
        cout << "Exiting as weights are incorrect" << endl;
        exit(42);
    }

}

//        first window
//        portfolio.balance(returns[0:99])
//        portfolio.backtest(returns[100:111])
//
//        second window
//        portfolio.balance(returns[12:111])
//        portfolio.backtest(returns[112:123])
