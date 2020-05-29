//

#include <sstream>
#include "DataRepository.h"

int run(string filename, int nAssets, int nDays);

int main(int argc, char *argv[]) {

    int testNAssets = 2;
    int testNDays = 4;
    int numberAssets = 83;
    int numberDays = 700;

    string fullFile = "../asset_returns.csv";
    string testFile = "../test_asset_returns.csv";

    run(testFile, testNAssets, testNDays);

    return 0;
}

int run(string filename, int nAssets, int nDays) {
    Matrix returns = Matrix(nDays, nAssets);

    DataRepository repo = DataRepository(filename, nAssets, nDays);

    repo.readData(&returns);
    returns.print();

    Matrix A = Matrix(2, 2);
    A.set(0, 0, 1);
    A.set(0, 1, 2);
    A.set(1, 0, 3);
    A.set(1, 1, 4);

    Matrix B = Matrix(2, 2);
    B.set(0, 0, 5);
    B.set(0, 1, 6);
    B.set(1, 0, 7);
    B.set(1, 1, 8);

    Matrix C = A.multiply(B);
    A.print();
    B.print();
    C.print();

    return 0;
}
