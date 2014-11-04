#include "mygraph.hpp"
#include "exception.hpp"
#include "floydwarschall.hpp"
#include "dijkstra.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>

using namespace std;

void printMatrix(ofstream & ofs, double ** matrix, unsigned int size) {
    for(unsigned int k = 0; k < size; ++k)
        for(unsigned int i = k+1; i < size; ++i)
            if(matrix[k][i] != numeric_limits<double>::max())
                ofs << k << " " << i << " " << matrix[k][i] << endl;
}


/**
 * Kompilace: $ g++ -std=c++11 -Wall -pedantic main.cpp mygraph.cpp edge.cpp node.cpp dijkstra.cpp -o graph
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

                clock_t begin = clock();
                ofs.open("dijkstra.out");
                if(!ofs.is_open()) throw IOException();

                double ** matrix;
                CDijkstra dijkstra = CDijkstra(graph);
                matrix = dijkstra.CalculateDistanceMatrix();
                printMatrix(ofs, matrix, graph->size());
                ofs.close();
                clock_t end = clock();
                double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

                cout << "Dijkstra:\t" << elapsed_secs << " sec" << endl;

                begin = clock();
                ofs.open("floydwarshall.out");
                if(!ofs.is_open()) throw IOException();

                matrix = floydWarschall(graph);
                printMatrix(ofs, matrix, graph->size());
                ofs.close();
                end = clock();
                elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

                cout << "FloydWarshall:\t" << elapsed_secs << " sec" << endl;

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
