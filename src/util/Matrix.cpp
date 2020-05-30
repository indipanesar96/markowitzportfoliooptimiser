#include <cstdlib>
#include <sstream>
#include "csv.h"
#include <vector>
#include "../DataRepository.h"
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
    for (int i = 0; i < nRows; ++i) {
        for (int j = 0; j < nCols; ++j) {
            matrix[i][j] = 0.0;
        }
    }
}


double Matrix::get(int n, int i) {
    checkInputRowColDimensions(n, i);
    return matrix[n][i];
}


void Matrix::checkInputRowColDimensions(int inputNRows, int inputNCols) const {
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

vector<double> Matrix::multiplyVector(vector<double> *vec) {

    int finalLength = vec->size();

    checkDimsForMultiplication(finalLength);

    vector<double> result = vector<double>(finalLength);

    cout << "hi"<<endl;
    for (int r = 0; r < nRows; r++) {
        double temp = 0.0;
        for (int c = 0; c < nCols; c++) {
            temp += matrix[r][c] * vec->at(c);
        }
        result.at(r) = temp;
    }
    return result;
}

void Matrix::set(int row, int col, double value) {
    checkInputRowColDimensions(row, col);
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

    const int aRows = matrix.size();
    const int aCols = matrix[0].size();
    const int bCols = B.getNCols();
    const int bRows = B.getNRows();

    if (aRows == bRows && aCols == bCols) {
        for (int i = 0; i < aRows; ++i) {
            for (int j = 0; j < aCols; ++j) {
                C.set(i, j, matrix[i][j] + B.get(i, j));
            }
        }
        return C;
    } else {
        cout << "Matrix A and B don't have the same dimensions:" <<
             "\n\tMatrix A Dim: (" << aRows << ", " << aCols << ")" <<
             "\n\tMatrix B Dim: (" << bRows << ", " << bCols << ")" << endl;
        exit(1);

    }
}

void Matrix::checkDimsForMultiplication(int bRows) const {
    // first matrix for multiplication is always self
    // ie A.multiply(B), then nCols is the number of columns in A
    if (nCols != bRows) {
        cout << "Matrix A cols must = matrix B rows:" <<
             "\n\tMatrix A cols:  " << nCols <<
             "\n\tMatrix B rows:  " << bRows << endl;
        exit(1);
    }
}

Matrix Matrix::multiply(Matrix &B) {
    Matrix C = Matrix(matrix.size(), B.getNCols());

    const int bCols = B.getNCols();
    const int bRows = B.getNRows();

    checkDimsForMultiplication(bRows);

    double temp = 0.0;
    for (int i = 0; i < nRows; ++i) {
        for (int j = 0; j < bCols; ++j) {
            for (int k = 0; k < nCols; ++k) {
                temp += matrix[i][k] * B.get(k, j);
                if (k == nCols - 1) {
                    C.set(i, j, temp);
                    temp = 0.0;
                }
            }
        }
    }
    return C;
}


void Matrix::checkRowColExists(int n, bool checkRow) const {

    if (checkRow) {
        if (n < 0 || n > nRows) {
            cout << "Invalid row number!" << endl;
            cout << "\tNRows: " << nRows << " you chose: " << n << endl;
            exit(1);
        }
    } else {
        if (n < 0 || n > nCols) {
            cout << "Invalid column number!" << endl;
            cout << "\tNCols: " << nCols << " you chose: " << n << endl;
            exit(1);
        }
    }


}


vector<double> Matrix::getRow(int i) {
    checkRowColExists(i, true);
    return matrix[i];
}

vector<double> Matrix::getCol(int i) {
    checkRowColExists(i, false);
    vector<double> column = vector<double>(nRows);

    for (int r = 0; r < nRows; r++) {
        double columnValueForThisRow = matrix[r][i];
        column[r] = columnValueForThisRow;
    }

    return column;
}

Matrix Matrix::get(int rowStart, int rowEnd, int colStart, int colEnd) {
    // end of each range is not included
    // i.e. get(2, 4, 3, 6) will return a matrix of shape (2, 3)
    // consisting of rows 2 and 3 and columns 3,4,5

    if (rowStart >= rowEnd || colStart >= colEnd) {
        cout << "Index start positions must be before the end positions:" << endl;
        cout << "\tRow Start: " << rowStart << ", Row End: " << rowEnd << endl;
        cout << "\tCol Start: " << colStart << ", Col End: " << colEnd << endl;
        exit(1);
    }

    if (rowEnd > nRows || colEnd > nCols || rowStart < 0 || colStart < 0) {
        cout << "Indices out of bounds:" << endl;
        cout << "\tRows in matrix: " << nRows << endl;
        cout << "\tCols in matrix: " << nCols << endl;
        cout << "\tYou tried: Row Start " << rowStart << ", Row End " << rowEnd << endl;
        cout << "\tYou tried: Col Start " << colStart << ", Col End " << colEnd << endl;
        exit(1);
    }

    int newMatrixRows = rowEnd - rowStart;
    int newMatrixCols = colEnd - colStart;

    Matrix res = Matrix(newMatrixRows, newMatrixCols);

    for (int i = 0; i < newMatrixRows; i++) {
        for (int j = 0; j < newMatrixCols; j++) {
            res.set(i, j, matrix[rowStart + i][colStart + j]);
        }
    }
    return res;
}


