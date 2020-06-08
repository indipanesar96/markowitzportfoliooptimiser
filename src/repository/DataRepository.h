#ifndef MARKOWITZPORTFOLIOOPTIMISER_DATAREPOSITORY_H
#define MARKOWITZPORTFOLIOOPTIMISER_DATAREPOSITORY_H

#include <cstring>
#include "../util/Matrix.h"
using namespace std;
class DataRepository {

    string fileName;
    int nAssets;

public:
    DataRepository(string &fileName_, int nAssets_) {
        fileName = fileName_;
        nAssets = nAssets_;
    }

    void readData(Matrix *matrix);

    static double string_to_double(const string &s);

};

#endif //MARKOWITZPORTFOLIOOPTIMISER_DATAREPOSITORY_H
