#include <sstream>
#include "Backtester.cpp"
#include "util/RunConfig.h"

int main(int argc, char *argv[]) {
    RunConfig small = RunConfig(0.5, 0.5, 9, 2, "../resources/test_asset_returns.csv");
    RunConfig medium = RunConfig(0.5, 0.5, 50, 4, "../resources/medium_asset_returns.csv");
    RunConfig large = RunConfig(0.5, 0.5, 700, 83, "../resources/asset_returns.csv");

    Backtester b;
//    b.run(small);
    b.run(medium);
//    b.run(large);

    return 0;
}

