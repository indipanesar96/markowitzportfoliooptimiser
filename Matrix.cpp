//
// Created by indy_ on 28/05/2020.
//

#include <cstdlib>
#include <sstream>
#include "csv.h"
#include <vector>
#include "DataRepository.h"
#include "Matrix.h"
#include <stdexcept>

using namespace std;


Matrix::Matrix(int nRows_, int nCols_) {

    if (nRows_ < 1) {
//        throw invalid_argument("nRows of matrix must be >1 !");
        cout << "nRows of matrix must be >1 !" << endl;
        exit(1); // this is suboptimal - no destructors called
    }
    if (nCols_ < 1) {
//        throw invalid_argument("nCols of matrix must be >1 !");
        cout << "nCols of matrix must be >1 !" << endl;
        exit(1); // this is suboptimal - no destructors called
    }

    nCols = nCols_;
    nRows = nRows_;
    matrix.resize(nRows);

    for (int r = 0; r <= nRows; r++) {
        matrix[r].resize(nCols);
    }
}


double Matrix::get(int n, int i) {
    checkRowColDimensions(n, i);
    return matrix[n][i];
}


void Matrix::checkRowColDimensions(int inputNRows, int inputNCols) const {
    if (inputNRows < 0 || inputNRows > nRows) {
        cout << "Matrix has " << nRows
             << " rows, cannot access row: " << inputNRows << endl;
        exit(1);
    }

    if (inputNCols < 0 || inputNCols > nCols) {
        cout << "Matrix has " << nCols
             << " columns, cannot access column: " << inputNCols << endl;
        exit(1);
    }
}


void Matrix::set(int row, int col, double value) {
    checkRowColDimensions(row, col);
    matrix[row][col] = value;
}


int Matrix::getNRows() const {
    return nRows;
}


int Matrix::getNCols() const {
    return nCols;
}


void Matrix::print() {
    cout << setiosflags(ios::fixed)
         << setprecision(4);
    for (const vector<double> &row : matrix) {
        for (double element : row) {
            cout << element << '\t';
        }
        cout << endl;
    }
    cout << endl;
}

Matrix Matrix::add(Matrix &B) {
    Matrix C = Matrix(matrix.size(), B.getNCols());

    const int aRows = matrix.size();     // a rows
    const int aCols = matrix[0].size();  // a cols
    const int bCols = B.getNCols();  // b cols
    const int bRows = B.getNRows();  // b rows

    if (aRows == bRows && aCols == bCols) {
        double temp = 0.0;
        for (int i = 0; i < aRows; ++i) {
            for (int j = 0; j < aCols; ++j) {
                C.set(i, j, matrix[i][j] + B.get(i, j));
            }
        }
        return C;
    } else {
        cout << "Matrix A cols must = matrix B rows:" <<
             "\n\tMatrix A cols:  " << aCols <<
             "\n\tMatrix B rows:  " << bRows << endl;
        exit(1);

    }
}

Matrix Matrix::multiply(Matrix &B) {
    Matrix C = Matrix(matrix.size(), B.getNCols());

    const int aRows = matrix.size();     // a rows
    const int aCols = matrix[0].size();  // a cols
    const int bCols = B.getNCols();  // b cols
    const int bRows = B.getNRows();  // b rows

    if (aCols != bRows) {
        cout << "Matrix A cols must = matrix B rows:" <<
             "\n\tMatrix A cols:  " << aCols <<
             "\n\tMatrix B rows:  " << bRows << endl;
        exit(1);

    } else {
        double temp = 0.0;
        for (int i = 0; i < aRows; ++i) {
            for (int j = 0; j < bCols; ++j) {
                for (int k = 0; k < aCols; ++k) {
                    temp += matrix[i][k] * B.get(k, j);
                    if (k == aCols - 1) {
                        C.set(i, j, temp);
                        temp = 0.0;
                    }
                }
            }
        }
        return C;
    }
}
