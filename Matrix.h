//
// Created by indy_ on 28/05/2020.
//

#ifndef MARKOWITZPORTFOLIOOPTIMISER_MATRIX_H
#define MARKOWITZPORTFOLIOOPTIMISER_MATRIX_H

#include <iomanip>
#include <vector>
#include <iostream>

using namespace std;

class Matrix {
private:
    int nRows;
    int nCols;
    vector<vector<double>> matrix;
    // to store rows and then columns
    // matrix = <<a11, a12, a13>, <a21, a22, a23>> for a 2x3 matrix

    void checkRowColDimensions(int n, int m) const;

public:
    Matrix(int nRows_, int nCols_);

    int getNRows() const;

    int getNCols() const;

    void set(int row, int col, double value);

    double get(int n, int i);

    Matrix multiply(Matrix &m1);

    void print();
};

#endif //MARKOWITZPORTFOLIOOPTIMISER_MATRIX_H
