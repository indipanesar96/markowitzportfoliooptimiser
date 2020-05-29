
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include "util/csv.h"
#include <cstring>
#include "DataRepository.h"
#include "util/Matrix.h"

using namespace std;


void DataRepository::readData(Matrix* matrix) {
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
                matrix->set(i, j, temp);
            }
            i++;
        }
        file.close();
    } else {
        cout << fileName << " missing\n";
        exit(0);
    }
}


double DataRepository::string_to_double(const std::string &s) {
    std::istringstream i(s);
    double x;
    if (!(i >> x))
        return 0;
    return x;
}
                                                                    
