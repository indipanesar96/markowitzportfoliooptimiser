#ifndef MARKOWITZPORTFOLIOOPTIMISER_VECTORUTIL_H
#define MARKOWITZPORTFOLIOOPTIMISER_VECTORUTIL_H

#include <vector>
#include <iostream>
#include <type_traits>
#include <algorithm>

// template type that allows a generic type but ensures it is numeric
// eg strings can't be passed
template<typename T,
        typename = typename enable_if<is_arithmetic<T>::value, T>::type>
vector<T> vectorLinearCombination(T aCoeff, vector<T> *a, T bCoeff, vector<T> *b) {
    // for operations like result = aCoefficient * A + bCoefficient * B
    // where aCoefficient and bCoefficient are scalars

    int aSize = a->size();
    int bSize = b->size();
    if (aSize != bSize) {
        cout << "Vectors aren't the same size and so cannot be subtracted from one another." << endl;
        cout << "\t Sizes: " << aSize << " and " << bSize;
        exit(12);
    }
    vector<double> result = vector<double>(aSize);
    for (int i = 0; i < aSize; i++) {
        result[i] = aCoeff * a->at(i) + bCoeff * b->at(i);
    }

    return result;
}

template<typename T,
        typename = typename enable_if<is_arithmetic<T>::value, T>::type>
T countNegative(const vector<T> &elems) {
    // count how many elements are negative, used for determining the number of shorts
    return count_if(elems.begin(), elems.end(), [](T x) { return x < 0; });
}

template<typename T,
        typename = typename enable_if<is_arithmetic<T>::value, T>::type>
T innerProduct(vector<T> *a, vector<T> *b) {
    // calculate inner product of two vectors, with some error checking

    int aSize = a->size();
    int bSize = b->size();
    if (aSize != bSize) {
        cout << "Vectors aren't the same size and so cannot be subtracted from one another." << endl;
        cout << "\t sizes: " << aSize << " and " << bSize;
        exit(37);
    }
    return inner_product(begin(*a), end(*a), begin(*b), 0.0);
}


template<typename T>
void printVector(vector<T> *toBePrinted) {
    // for debugging
    for (T elem: *toBePrinted) {
        cout << elem << endl;
    }
}

#endif //MARKOWITZPORTFOLIOOPTIMISER_VECTORUTIL_H
