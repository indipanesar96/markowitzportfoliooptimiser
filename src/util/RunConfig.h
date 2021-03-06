#ifndef MARKOWITZPORTFOLIOOPTIMISER_RUNCONFIG_H
#define MARKOWITZPORTFOLIOOPTIMISER_RUNCONFIG_H

#include <cmath>
#include <string>
#include <cstdlib>

using namespace std;
// to store all input parameters in a nice clean way instead of passing
// all individually to Portfolio::backtest()
class RunConfig {

public:
    RunConfig(
            double initialLambda_,
            double initialMu_,
            int nDays_,
            int nAssets_,
            int tWindowLength_,
            int bWindowLength_,
            string fileName_
    ) {
        initialLambda = initialLambda_;
        initialMu = initialMu_;
        nAssets = nAssets_;
        nDays = nDays_;
        fileName = fileName_;
        tWindowLength = tWindowLength_;
        bWindowLength = bWindowLength_;
    }

    void setNAssets(int n_) {
        nAssets = n_;
    }

    double WEIGHTSTOLERANCE = pow(10, -3);
    double initialLambda;
    double initialMu;
    int nAssets;
    int nDays;
    string fileName;
    double EPSILON = pow(10, -6);
    int bWindowLength = 100; //days;
    int tWindowLength = 12; //days;

};

#endif //MARKOWITZPORTFOLIOOPTIMISER_RUNCONFIG_H

