//
// Created by indy_ on 28/05/2020.
//

#ifndef MARKOWITZPORTFOLIOOPTIMISER_MATRIX_H
#define MARKOWITZPORTFOLIOOPTIMISER_MATRIX_H

#include <iomanip>
#include <vector>
#include <iostream>

using namespace std;

template<typename T>
class Matrix {
private:
    int nRows;
    int nCols;
    vector<vector<T>> matrix;
    void checkInput(int n, int m);
public:
    Matrix(int nRows_, int nCols_);

    int getNRows();

    int getNCols();

    void setElement(int row, int col, T value);

    T getElement(int n, int i);

    void display();
};

#endif //MARKOWITZPORTFOLIOOPTIMISER_MATRIX_H
