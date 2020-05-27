
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include "csv.h"
#include <cstring>


//g++ -c read_data.cpp
// g++ -c csv.cpp
// g++ -o portfolioSolver csv.o read_data.o
// ./portfolioSolver
/*
import numpy as np
A = np.array([[1., 2.], [3., 4.]])
b = np.array([[5],[6]])
x = np.linalg.solve(A,b)
*/

double string_to_double(const std::string &s);

int readData(double **data, string fileName);


int main(int argc, char *argv[]) {

//    int numberAssets = 2;
//    int numberReturns = 4;
    int numberAssets = 83;
    int numberReturns = 700;
    // dynamic memory allocation (new command)
    // you can vary the number of assets and returns
    // returnMatrix is an array of pointers, this line is creating the columns
    double **returnMatrix = new double *[numberAssets]; // a matrix to store the return data
    //allocate memory for return data

    for (int i = 0; i < numberAssets; i++)
        /// creates the rows of the matrix
        returnMatrix[i] = new double[numberReturns];

    //read the data from the file and store it into the return matrix
    string fileName = "../asset_returns.csv";
    int something = readData(returnMatrix, fileName);
    cout << something << endl;
    cout << "hello" << endl;

    //example on how to calculate the average return
    double mean = 0;
    for (int i = 0; i < numberAssets; i++) {
        mean = 0;
        for (int j = 0; j < numberReturns; j++) {
            double temp = returnMatrix[i][j];
            // returnMatrix[i][j] stores the asset i, return j value
            cout << "Asset " << i << ", Return " << j << "=" << temp << "\n";
            mean = mean + temp / numberReturns;
        }
    }

    for (int i = 0; i < numberAssets; i++)
        delete[] returnMatrix[i];
    delete[] returnMatrix;


    return 0;
}


double string_to_double(const std::string &s) {
    std::istringstream i(s);
    double x;
    if (!(i >> x))
        return 0;
    return x;
}

int readData(double **data, string fileName) {
    char tmp[20];
    ifstream file(strcpy(tmp, fileName.c_str()));
    Csv csv(file);
    string line;
    if (file.is_open()) {
        int i = 0;
        // i = return number ie day number
        // j = asset number
        while (csv.getline(line) != 0) {
            for (int j = 0; j < csv.getnfield(); j++) {
                double temp = string_to_double(csv.getfield(j));
//                cout << "Asset " << j << ", Return "<<i<<"="<< temp<<"\n";
                data[j][i] = temp;
            }
            i++;
        }
        file.close();
    } else {
        cout << fileName << " missing\n";
        exit(0);
    }
    cout << "end of functiuon" << endl;
    return 0;
}
                                                                    
