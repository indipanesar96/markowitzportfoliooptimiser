#include "Portfolio.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>

using namespace std;


void Portfolio::addWeightsToHistory(vector<double> &weights) {
    this->weightsHistory.push_back(weights);
}

Portfolio::Portfolio(RunConfig config_) {
    config = config_;
    allReturns = Matrix(config_.nDays, config_.nAssets);

    DataRepository(config_.fileName).readData(&allReturns);

    nWindows = (config.nDays - config.bWindowLength) / config.tWindowLength;

    optimiser = PortfolioOptimiser(config_.EPSILON,
                                   config_.initialLambda,
                                   config_.initialMu,
                                   config_.nAssets);
}

Results Portfolio::backtest(double dailyReturn) {
    // assets is columns, rows are days: C_ij = ith asset, jth day

    optimiser.setTargetDailyReturn(dailyReturn);

    int tWindowLength = config.tWindowLength;
    int bWindowLength = config.bWindowLength;

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

        vector<double> portfolioWeights = this->balance(&balanceWindow);

        portReturnsOOS[currentWindow] = this->evaluate(&testWindow, &portfolioWeights);
        portReturnsIS[currentWindow] = this->evaluate(&balanceWindow, &portfolioWeights);

        currentWindow += 1;
    }

    double avePortReturnOOS = ParameterEstimator::calculateMean(&portReturnsOOS);
    double avePortReturnIS = ParameterEstimator::calculateMean(&portReturnsIS);

    double stdOOS = ParameterEstimator::calculateStd(&portReturnsOOS);
    double stdIS = ParameterEstimator::calculateStd(&portReturnsIS);


    return Results{avePortReturnOOS, avePortReturnIS, stdOOS, stdIS};
}

double Portfolio::evaluate(Matrix *m, vector<double> *weights) const {

    vector<double> aveAssetReturns = ParameterEstimator::estimateMultipleMeans(m);

    // could swap with a call to innerProduct

    double portReturn = 0;
    for (int asset = 0; asset < config.nAssets; asset++) {
        portReturn += aveAssetReturns[asset] * weights->at(asset);
    }
    return portReturn;
}


vector<double> Portfolio::balance(Matrix *m) {
    vector<double> meanReturns = ParameterEstimator::estimateMultipleMeans(m);
    Matrix cov = ParameterEstimator::estimateCovariances(m, &meanReturns);

    vector<double> weights = optimiser.calculateWeights(&cov, &meanReturns);
    this->checkWeights(weights);
    this->addWeightsToHistory(weights);
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

//        first window
//        optimiser.balance(returns[0:99])
//        optimiser.backtest(returns[100:111])
//
//        second window
//        optimiser.balance(returns[12:111])
//        optimiser.backtest(returns[112:123])
