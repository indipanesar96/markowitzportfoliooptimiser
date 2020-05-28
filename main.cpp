//

#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <cstring>

#include "csv.h"
#include "main.h"
#include "DataRepository.h"
#include "Matrix.h"
#include "Matrix.cpp"


int main(int argc, char *argv[]) {

    int numberAssets = 2;
    int numberDays = 4;
//    int numberAssets = 83;
//    int numberDays = 700;

    string fullFile = "../asset_returns.csv";
    string testFile = "../test_asset_returns.csv";

    // dynamic memory allocation (new command)
    // you can vary the number of assets and returns
    // returnMatrix is an array of pointers, this line is creating the columns
    // a matrix to store the return data
    //allocate memory for return data



    Matrix<double> returns = Matrix<double>(numberAssets, numberDays);

    double **returnMatrix = new double *[numberAssets];

    for (int i = 0; i < numberAssets; i++)
        /// creates the nRows of the matrix
        returnMatrix[i] = new double[numberDays];

    //read the data from the file and store it into the return matrix

    DataRepository repo = DataRepository(testFile, numberAssets, numberDays);

    repo.readData(returnMatrix);

    //example on how to calculate the average return
    double mean = 0;
    for (int i = 0; i < numberAssets; i++) {
        mean = 0;
        for (int j = 0; j < numberDays; j++) {
            double temp = returnMatrix[i][j];
            // returnMatrix[i][j] stores the asset i, return j value
            cout << "Asset " << i << ", Return " << j << "=" << temp << "\n";
            mean = mean + temp / numberDays;
        }
    }

    for (int i = 0; i < numberAssets; i++)
        delete[] returnMatrix[i];
    delete[] returnMatrix;


    return 0;
}
