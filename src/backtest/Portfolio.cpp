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

    optimiser = PortfolioOptimiser(config_.EPSILON,
                                   config_.initialLambda,
                                   config_.initialMu,
                                   config_.nAssets,
                                   config_.nDays);
}

int Portfolio::run(double dailyReturn) {
    // assets is columns, rows are days: C_ij = ith asset, jth day

    optimiser.setTargetDailyReturn(dailyReturn);

    bool printIndices = true;
    for (int day = 0; day + bWindowLength + tWindowLength - 1 < config.nDays; day += 12) {

//        first window
//        portfolio.balance(returns[0:99])
//        portfolio.backtest(returns[100:111])
//
//        second window
//        portfolio.balance(returns[12:111])
//        portfolio.backtest(returns[112:123])

        int bStart = day;
        int bEnd = day + bWindowLength - 1;
        int tStart = day + bWindowLength;
        int tEnd = day + bWindowLength + tWindowLength - 1;

        Matrix balanceWindow = allReturns.get(
                bStart,
                bEnd,
                0,
                config.nAssets);

        Matrix testWindow = allReturns.get(
                tStart,
                tEnd,
                0,
                config.nAssets);

        if (printIndices) {

            cout << endl;
            cout << day << endl;
            cout << "bStart: " << bStart << " bEnd: " << bEnd << endl;
            cout << "tStart: " << tStart << " tEnd: " << tEnd << endl;
        }


        vector<double> portfolioWeights = this->balance(&balanceWindow);
        int something = this->evaluate(&testWindow, &portfolioWeights);


        if (day == 7000) {

            cout << "done" << endl;
            exit(10);
        }
    }

    return 0;
}

int Portfolio::evaluate(Matrix *m, vector<double> *weights) {
    return 0;
}


vector<double> Portfolio::balance(Matrix *m) {
    vector<double> meanReturns = estimator.estimateMeanReturns(m);
    Matrix cov = estimator.estimateCovariances(m, &meanReturns);
    vector<double> weights = optimiser.calculateWeights(&cov, &meanReturns);
    this->checkWeights(weights);
    this->addWeightsToHistory(weights);
    return weights;

}

void Portfolio::checkWeights(vector<double> &w) {

    long sum = accumulate(w.begin(), w.end(), 0.0);
    cout << "The sum of the weights is: " << sum << endl;

    if (sum != 1) {
        exit(42);
    }

}

