#ifndef MARKOWITZPORTFOLIOOPTIMISER_BACKTESTRESULTS_H
#define MARKOWITZPORTFOLIOOPTIMISER_BACKTESTRESULTS_H

struct BacktestResults {
    double retOOS;
    double retIS;
    double stdOOS;
    double stdIS;
};

struct PortfolioMetrics {
    double returns;
    double covariance;
};

#endif //MARKOWITZPORTFOLIOOPTIMISER_BACKTESTRESULTS_H
