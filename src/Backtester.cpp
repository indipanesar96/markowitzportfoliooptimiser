//
// Created by indy_ on 29/05/2020.
//

#include "Backtester.h"
#include "util/Matrix.h"
#include "DataRepository.h"

int Backtester::run(string filename, int nAssets, int nDays) {
    Matrix all_returns = Matrix(nDays, nAssets);

    DataRepository repo = DataRepository(filename, nAssets, nDays);

    repo.readData(&all_returns);
    all_returns.print();

    Matrix A = Matrix(3, 2);
    A.set(0, 0, 1);
    A.set(0, 1, 2);
    A.set(1, 0, 3);
    A.set(1, 1, 4);
    A.set(2, 0, 5);
    A.set(2, 1, 6);

    Matrix B = Matrix(2, 3);
    B.set(0, 0, 7);
    B.set(0, 1, 8);
    B.set(0, 2, 9);
    B.set(1, 0, 10);
    B.set(1, 1, 11);
    B.set(1, 2, 12);

    Matrix C = A.multiply(B);
    A.print();
    B.print();
    C.print();


    int bWindowLength = 100; //days
    int tWindowLength = 12; //days

    // assets is columns, rows are days: C_ij = ith asseth, jth day

    Matrix indexed = all_returns.get(2,4,0,3);

    indexed.print();

    return 0;

}