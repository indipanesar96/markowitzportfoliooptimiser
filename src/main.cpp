//

#include <sstream>
#include "DataRepository.h"

int run(string filename, int nAssets, int nDays);

int main(int argc, char *argv[]) {

    int testNAssets = 2;
    int testNDays = 4;
    int numberAssets = 83;
    int numberDays = 700;

    string fullFile = "../resources/asset_returns.csv";
    string testFile = "../resources/test_asset_returns.csv";

    run(testFile, testNAssets, testNDays);
//    run(fullFile, numberAssets, numberDays);

    return 0;
}

int run(string filename, int nAssets, int nDays) {
    Matrix returns = Matrix(nDays, nAssets);

    DataRepository repo = DataRepository(filename, nAssets, nDays);

    repo.readData(&returns);
    returns.print();

    return 0;
}
