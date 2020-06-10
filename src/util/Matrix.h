#ifndef MARKOWITZPORTFOLIOOPTIMISER_MATRIX_H
#define MARKOWITZPORTFOLIOOPTIMISER_MATRIX_H

#include <iomanip>
#include <vector>
#include <iostream>

using namespace std;

class Matrix {
private:
    int nRows{};
    int nCols{};
    vector<vector<double>> matrix{};
    // to store rows and then columns
    // C (matrix) = <<a11, a12, a13>, <a21, a22, a23>> for a 2x3 matrix
    // assets is columns, rows are days: C_ij = ith day, jth asset

    void checkInputRowColDimensions(int n, int m) const;

    void checkRowColExists(int n, bool checkRow) const;

    void checkDimsForMultiplication(int bRows) const;


public:
    Matrix(int nRows_, int nCols_);

    int getNRows() const;

    int getNCols() const;

    void set(int row, int col, double value);

    double get(int n, int i);

    Matrix get(int rowStart, int rowEnd, int colStart, int colEnd);

    Matrix getAllCols(int rowStart, int rowEnd);

    void print();

    vector<double> getCol(int i);

    vector<double> multiplyVector(vector<double> *vec);

    Matrix multiply(Matrix *B);

    void setCol(int i, vector<double> *values);
};

#endif //MARKOWITZPORTFOLIOOPTIMISER_MATRIX_H
