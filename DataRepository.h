//
// Created by indy_ on 28/05/2020.
//

#ifndef MARKOWITZPORTFOLIOOPTIMISER_DATAREPOSITORY_H
#define MARKOWITZPORTFOLIOOPTIMISER_DATAREPOSITORY_H
#include <cstring>

class DataRepository{

    string fileName;
    int n_assets;
    int n_days;


public:
    DataRepository(string& fileName_, int num_assets_, int num_days_){
        fileName = fileName_;
        n_assets = num_assets_;
        n_days = num_days_;
    }
    void readData(double **data);
    double string_to_double(const std::string &s);

};

#endif //MARKOWITZPORTFOLIOOPTIMISER_DATAREPOSITORY_H
