#include "mygraph.hpp"
#include <limits>

using namespace std;

void floydMarschall(MyGraph * graph) {
    double ** matrix = graph->getMatrix();
    unsigned int size = graph->size();

    for(unsigned int k = 0; k < size; ++k)
        for(unsigned int i = 0; i < size; ++i)
            for(unsigned int j = 0; j < size; ++j) {
                matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
            }

    for(unsigned int k = 0; k < size; ++k)
        for(unsigned int i = k+1; i < size; ++i)
            if(matrix[k][i] != numeric_limits<double>::max())
                cout << k << " " << i << " " << matrix[k][i] << endl;

}
