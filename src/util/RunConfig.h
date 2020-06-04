#ifndef MARKOWITZPORTFOLIOOPTIMISER_RUNCONFIG_H
#define MARKOWITZPORTFOLIOOPTIMISER_RUNCONFIG_H
//#include <iostream>

#include <cmath>
#include <string>
#include <cstdlib>

using namespace std;
class RunConfig{

public:
    RunConfig(
            double initialLambda_,
            double initialMu_,
            int nDays_,
            int nAssets_,
            string fileName_
            ){
        initialLambda = initialLambda_;
        initialMu = initialMu_;
        nAssets = nAssets_;
        nDays = nDays_;
        fileName = fileName_;
    }
    double initialLambda;
    double initialMu;
    int nAssets;
    int nDays;
    string fileName;
    double EPSILON = pow(10, -6);
};

#endif //MARKOWITZPORTFOLIOOPTIMISER_RUNCONFIG_H
