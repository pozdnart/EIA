#include "mygraph.hpp"
#include <limits>
#include <omp.h>
#include <emmintrin.h>

using namespace std;

#define numberOfChunk 1

double ** floydWarschall(MyGraph * graph, int & s) {
    double ** matrix = graph->getMatrix();
    int size = (int)graph->size();

    int numBlocks = size / s;


    int bs = 0;
    int b1s = s;

    #pragma omp parallel firstprivate(bs,b1s) num_threads(4)
    while(bs < size) { // Kazdej blok to zpracuje
        #pragma omp  for schedule(static,numberOfChunk)
        for(int k = bs; k < b1s; ++k) { // tohle zpracuje samotny blok
            for(int i = bs; i < b1s; ++i) {
                for(int j = bs; j < b1s; j += 2) {
                    __m128d sums = _mm_add_pd(_mm_load_pd1(&matrix[i][k]), _mm_load_pd(&matrix[k][j]));
                    __m128d in = _mm_load_pd(&matrix[i][j]);
                    _mm_store_pd(&matrix[i][j], _mm_min_pd(in, sums));
                }
            }
        }

        #pragma omp  for schedule(static,numberOfChunk)
        for(int ib = 0; ib < numBlocks; ++ib) { // pak bloky ve stejnym sloupci
            int ib1s = (ib+1) * s;
            int ibs = ib * s;
            for(int k = bs; k < b1s; ++k) {
                for(int i = bs; i < b1s; ++i) {
                    for(int j = ibs; j < ib1s; j += 2) {
                        __m128d sums = _mm_add_pd(_mm_load_pd1(&matrix[i][k]), _mm_load_pd(&matrix[k][j]));
                        __m128d in = _mm_load_pd(&matrix[i][j]);
                        _mm_store_pd(&matrix[i][j], _mm_min_pd(in, sums));
                    }
                }
            }
        }

        #pragma omp  for schedule(static,numberOfChunk)
        for(int jb = 0; jb < numBlocks; ++jb) { // pak bloky ve stejny rade
            int jb1s = (jb+1) * s;
            int jbs = jb * s;
            for(int k = bs; k < b1s; ++k) {
                for(int i = jbs; i < jb1s; ++i) {
                    for(int j = bs; j < b1s; j += 2) {
                        __m128d sums = _mm_add_pd(_mm_load_pd1(&matrix[i][k]), _mm_load_pd(&matrix[k][j]));
                        __m128d in = _mm_load_pd(&matrix[i][j]);
                        _mm_store_pd(&matrix[i][j], _mm_min_pd(in, sums));
                    }
                }
            }
        }

        #pragma omp  for collapse(2) schedule(static,numberOfChunk)
        for(int ib = 0; ib < numBlocks; ++ib) // secko ostatni
        for(int jb = 0; jb < numBlocks; ++jb) {
            int ib1s = (ib+1) * s;
            int jb1s = (jb+1) * s;
            for(int i = jb * s; i < jb1s; ++i) {
                for(int j = ib * s; j < ib1s; ++j) {
                    for(int k = bs; k < b1s; ++k) {
                        matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
                    }
                }
            }
        }

        bs = b1s;
        b1s += s;
    } // end block while

    return matrix;
}

