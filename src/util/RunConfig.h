#ifndef MARKOWITZPORTFOLIOOPTIMISER_RUNCONFIG_H
#define MARKOWITZPORTFOLIOOPTIMISER_RUNCONFIG_H

#include <cmath>
#include <string>
#include <cstdlib>

using namespace std;


struct RunConfig {

    double initialLambda;
    double initialMu;
    int nDays;
    int nAssets;
    int tWindowLength = 12; //days;
    int bWindowLength = 100; //days;
    string fileName;
    double EPSILON = pow(10, -7);
    double WEIGHTSTOLERANCE = pow(10, -3);
} Default;

#endif //MARKOWITZPORTFOLIOOPTIMISER_RUNCONFIG_H
