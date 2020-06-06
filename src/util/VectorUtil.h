#ifndef MARKOWITZPORTFOLIOOPTIMISER_VECTORUTIL_H
#define MARKOWITZPORTFOLIOOPTIMISER_VECTORUTIL_H

#include <vector>
#include <iostream>
#include <type_traits>

using namespace std;



template<typename T,
        typename = typename enable_if< is_arithmetic<T>::value, T> ::type>
vector<T> vectorSubtract(vector<T> *a, vector<T> *b) {

    int aSize = a->size();
    int bSize = b->size();
    if (aSize != bSize) {
        cout << "Vectors aren't the same size and so cannot be subtracted from one another." << endl;
        cout << "\t sizes: " << aSize << " and " << bSize;
        exit(1);
    }
    vector<double> result = vector<double>(aSize);
    for (int i = 0; i < aSize; i++) {
        result[i] = a->at(i) - b->at(i);
    }

    return result;
}

template<typename T,
        typename = typename enable_if< is_arithmetic<T>::value, T> ::type>
vector<T> vectorAdditions(double aCoeff, vector<T> *a, double bCoeff, vector<T> *b) {

    int aSize = a->size();
    int bSize = b->size();
    if (aSize != bSize) {
        cout << "Vectors aren't the same size and so cannot be subtracted from one another." << endl;
        cout << "\t sizes: " << aSize << " and " << bSize;
        exit(1);
    }
    vector<double> result = vector<double>(aSize);
    for (int i = 0; i < aSize; i++) {
        result[i] = aCoeff * a->at(i) + bCoeff* b->at(i);
    }

    return result;
}

template<typename T,
        typename = typename enable_if< is_arithmetic<T>::value, T> ::type>
T innerProduct(vector<T> *a, vector<T> *b) {

    int aSize = a->size();
    int bSize = b->size();
    if (aSize != bSize) {
        cout << "Vectors aren't the same size and so cannot be subtracted from one another." << endl;
        cout << "\t sizes: " << aSize << " and " << bSize;
        exit(1);
    }
    return inner_product(begin(*a), end(*a), begin(*b), 0.0);
}


template<typename T>
void print(vector<T> *toBePrinted) {
    for (T elem: *toBePrinted) {
        cout << elem << endl;
    }
}

#endif //MARKOWITZPORTFOLIOOPTIMISER_VECTORUTIL_H
