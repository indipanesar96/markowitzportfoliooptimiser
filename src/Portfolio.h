#ifndef MARKOWITZPORTFOLIOOPTIMISER_PORTFOLIO_H
#define MARKOWITZPORTFOLIOOPTIMISER_PORTFOLIO_H

#include <vector>
#include "util/VectorUtil.h"
#include <iostream>

class Portfolio {
private:
    vector <vector<double>> weightsHistory {};
public:
    void addWeightsToHistory(vector<double> weights);

};


#endif //MARKOWITZPORTFOLIOOPTIMISER_PORTFOLIO_H
