#include <sstream>
#include "Backtester.cpp"

int main(int argc, char *argv[]) {

    int testNAssets = 2;
    int testNDays = 9;
    int numberAssets = 83;
    int numberDays = 700;


    int mediumNAssets = 4;
    int mediumNDays = 50;

    string fullFile = "../resources/asset_returns.csv";
    string testFile = "../resources/test_asset_returns.csv";
    string mediumFile = "../resources/medium_asset_returns.csv";


    Backtester b;
//    b.run(mediumFile, mediumNAssets, mediumNDays);
    b.run(testFile, testNAssets, testNDays);
//    b.run(fullFile, numberAssets, numberDays);

    return 0;
}
