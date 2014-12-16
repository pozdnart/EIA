#include "mygraph.hpp"
#include "exception.hpp"
#include "floydwarschall.hpp"
#include "dijkstraBH.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <chrono>

using namespace std;

void printMatrix(ofstream & ofs, double ** matrix, unsigned int size) {
    for(unsigned int k = 0; k < size; ++k)
        for(unsigned int i = k+1; i < size; ++i)
            if(matrix[k][i] != numeric_limits<double>::max())
                ofs << k << " " << i << " " << matrix[k][i] << endl;
}


/**
 * g++ -std=c++11 -O3 -ffast-math -fopenmp main.cpp mygraph.cpp exception.hpp node.cpp edge.cpp floydwarschall.hpp dijkstraBH.cpp binary_heap.cpp -o graph
 * ./graph [string] ... Spusti program, nacte ze souboru.
 * ./graph [string] [unsigned int] [unsigned int] ... Generuje graf do souboru,
 * druhy parametr je pocet uzlu a treti parametr pocet hran, ktere v prumeru
 * vedou z nejakeho uzlu.
 */
int main(int argc, char* const argv[]) {
    ios::sync_with_stdio(false);
    MyGraph * graph = new MyGraph();

    try {
        switch(argc) {
            case 2: {
                graph->load(argv[1]);

                ofstream ofs;
                double ** matrix;

                ofs.open("dijkstra.out");
                if(!ofs.is_open()) throw IOException();


                CDijkstra dijkstra = CDijkstra(graph);
                double time1 = omp_get_wtime();
                matrix = dijkstra.CalculateDistanceMatrix();
                double time2 = omp_get_wtime();
                printMatrix(ofs, matrix, graph->size());

                cout << "Dijktsra: " << time2 - time1 << endl;

                ofs.close();

                //double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

                ofs.open("floydwarshall.out");
                if(!ofs.is_open()) throw IOException();

                int blockSize = 20;
                while(graph->size() % blockSize != 0) ++blockSize;

                time1 = omp_get_wtime();
                matrix = floydWarschall(graph, blockSize);
                time2 = omp_get_wtime();
                cout << "FloydWarshall: " << time2 - time1 << endl;

                printMatrix(ofs, matrix, graph->size());
                delete [] matrix;
                ofs.close();

                break;
            }
            case 4: {
                unsigned int n, pocetHran;
                string arg = argv[2];
                arg += " ";
                arg += argv[3];
                arg += " ";
                stringstream ss(arg);
                ss >> n;
                ss >> pocetHran;
                if(ss.eof() || ss.fail()) throw IOException();
                graph->graphGen(n, pocetHran, argv[1]);
                break;
            }
            default: {
                throw IllegalArgumentException();
                break;
            }
        }
    }
    catch(IOException) {}
    catch(IllegalArgumentException) {}
    catch(...) {
        cerr << "Neco se podelalo." << endl;
    }

    delete graph;

    return 0;
}
