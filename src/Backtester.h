
#ifndef MARKOWITZPORTFOLIOOPTIMISER_BACKTESTER_H
#define MARKOWITZPORTFOLIOOPTIMISER_BACKTESTER_H
#include <sstream>

using namespace std;

class Backtester {

public:
    int run(string filename, int nAssets, int nDays);

};


#endif