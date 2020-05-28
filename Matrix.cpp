//
// Created by indy_ on 28/05/2020.
//

#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include "csv.h"
#include <cstring>
#include "DataRepository.h"
#include "Matrix.h"
#include <stdexcept>

using namespace std;

template<typename T>
Matrix<T>::Matrix(int nRows_, int nCols_) {

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
    matrix.resize(nRows + 1);

    for (int r = 0; r <= nRows; r++) {
        matrix[r].resize(nCols + 1);
    }
}

template<typename T>
T Matrix<T>::getElement(int n, int i) {
    checkInput(n, i);
    return matrix[n][i];
}

template<typename T>
void Matrix<T>::checkInput(int inputNRows, int inputNCols) {
    if (inputNRows < 0 || inputNRows > nRows){
        cout << "Matrix has " << nRows
             << " rows, cannot access row: " << inputNRows << endl;
        exit(1);
    }

    if (inputNCols < 0 || inputNCols > nCols){
        cout << "Matrix has " << nCols
             << " columns, cannot access column: " << inputNCols << endl;
        exit(1);
    }
}

template<typename T>
void Matrix<T>::setElement(int row, int col, T value) {
    checkInput(row, col);
    matrix[row][col] = value;
}

template<typename T>
int Matrix<T>::getNRows() {
    return nRows;
}

template<typename T>
int Matrix<T>::getNCols() {
    return nCols;
}


template<typename T>
void Matrix<T>::display() {
    cout << setiosflags(ios::fixed)
         << setprecision(2);
    for (const vector<T> &row : matrix) {
        for (T element : row) {
            cout << element << ' ';
        }
        cout << endl;
    }
}