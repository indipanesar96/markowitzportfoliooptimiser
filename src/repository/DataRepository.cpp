
#include <fstream>
#include "csv.h"
#include "DataRepository.h"
using namespace std;


void DataRepository::readData(Matrix* matrix) {
    // predominantly unchanged from what Panos provided except line 22

    char tmp[100]; // this is the max size the filename can be, otherwise stack buffer overflow
    ifstream file(strcpy(tmp, fileName.c_str()));
    Csv csv(file);
    string line;
    if (file.is_open()) {
        int i = 0;
        // i = return number ie day number
        // j = asset number
        while (csv.getline(line) != 0) {

            // if we onl require nAssets, don't read in the whole row
            for (int j = 0; j < min(csv.getnfield(), nAssets); j++) {
                matrix->set(i, j, string_to_double(csv.getfield(j)));
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
                                                                    
