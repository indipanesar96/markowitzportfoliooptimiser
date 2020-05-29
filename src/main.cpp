//

#include <sstream>
#include "Backtester.cpp"


int main(int argc, char *argv[]) {

    int testNAssets = 3;
    int testNDays = 9;
    int numberAssets = 83;
    int numberDays = 700;

    string fullFile = "../resources/asset_returns.csv";
    string testFile = "../resources/test_asset_returns.csv";

    Backtester b;
    b.run(testFile, testNAssets, testNDays);
//    b.run(fullFile, numberAssets, numberDays);

    return 0;
}

