#include "mygraph.hpp"
#include <limits>

using namespace std;
/*
double ** floydWarschall(MyGraph * graph, int & i) {
    double ** matrix = graph->getMatrix();
    int size = (int)graph->size();

    for(int k = 0; k < size; ++k)
        for(int i = 0; i < size; ++i) {
            for(int j = 0; j < size; ++j) {
                matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
            }
        }

    return matrix;
}
*/
double ** floydWarschall(MyGraph * graph, int & s) {
    double ** matrix = graph->getMatrix();
    int size = (int)graph->size();

    int numBlocks = size / s;

    for(int b = 0; b < numBlocks; ++b) {
        int b1s = (b+1) * s;
        int bs = b * s;
        for(int k = bs; k < b1s; ++k) {
            for(int i = bs; i < b1s; ++i) {
                int j = bs;
                for(; j < b1s; j += 4) {
                    double s1, s2, s3, s4;
                    s1 = matrix[i][k] + matrix[k][j];
                    s2 = matrix[i][k] + matrix[k][j+1];
                    s3 = matrix[i][k] + matrix[k][j+2];
                    s4 = matrix[i][k] + matrix[k][j+3];
                    matrix[i][j] = min(matrix[i][j], s1);
                    matrix[i][j+1] = min(matrix[i][j+1], s2);
                    matrix[i][j+2] = min(matrix[i][j+2], s3);
                    matrix[i][j+3] = min(matrix[i][j+3], s4);
                }
                for(j -= 4; j < b1s; ++j)
                    matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
            }
        }

        for(int ib = 0; ib < numBlocks; ++ib) {
            int ib1s = (ib+1) * s;
            for(int k = bs; k < b1s; ++k) {
                for(int i = bs; i < b1s; ++i) {
                    int j = ib * s;
                    for(; j < ib1s; j += 4) {
                        double s1, s2, s3, s4;
                        s1 = matrix[i][k] + matrix[k][j];
                        s2 = matrix[i][k] + matrix[k][j+1];
                        s3 = matrix[i][k] + matrix[k][j+2];
                        s4 = matrix[i][k] + matrix[k][j+3];
                        matrix[i][j] = min(matrix[i][j], s1);
                        matrix[i][j+1] = min(matrix[i][j+1], s2);
                        matrix[i][j+2] = min(matrix[i][j+2], s3);
                        matrix[i][j+3] = min(matrix[i][j+3], s4);
                    }
                    for(j -= 4; j < ib1s; ++j)
                        matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
                    }
            }
        }

        for(int jb = 0; jb < numBlocks; ++jb) {
            int jb1s = (jb+1) * s;
            for(int k = bs; k < b1s; ++k) {
                for(int i = jb * s; i < jb1s; ++i) {
                    for(int j = bs; j < b1s; ++j)
                        matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
                    }
            }
        }

        for(int ib = 0; ib < numBlocks; ++ib)
        for(int jb = 0; jb < numBlocks; ++jb) {
            int ib1s = (ib+1) * s;
            int jb1s = (jb+1) * s;
            for(int i = jb * s; i < jb1s; ++i) {
                for(int j = ib * s; j < ib1s; ++j) {
                    int k = bs;
                    for(; k < b1s; k += 4) {
                        double s1, s2, s3, s4;
                        s1 = matrix[i][k] + matrix[k][j];
                        s2 = matrix[i][k+1] + matrix[k+1][j];
                        s3 = matrix[i][k+2] + matrix[k+2][j];
                        s4 = matrix[i][k+3] + matrix[k+3][j];
                        matrix[i][j] = min(matrix[i][j], min(min(s1,s2),min(s3,s4)));
                    }

                    for(k -= 4; k < b1s; ++k) {
                        matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
                    }
                }
            }
        }
    }

    return matrix;
}

