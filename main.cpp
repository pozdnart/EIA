#include "mygraph.hpp"
#include "exception.hpp"
#include <memory>
#include <iostream>
#include <sstream>

using namespace std;


/**
 * Kompilace: $ g++ -std=c++11 -Wall -pedantic main.cpp mygraph.cpp edge.cpp node.cpp -o graph
 * ./graph [string] ... Spusti program, nacte ze souboru.
 * ./graph [string] [double] [unsigned int] ... Generuje graf do souboru,
 * pravdepodobnost spojeni dvojice uzlu hranou, pocet uzlu.
 */
int main(int argc, char* const argv[]) {
    ios::sync_with_stdio(false);
    auto_ptr<MyGraph> graph(new MyGraph());

    try {
        switch(argc) {
            case 2: {
                graph->load(argv[1]);

                // TODO dijkstra(graph);
                // TODO floydMarschall(graph);

                break;
            }
            case 4: {
                int n;
                double d;
                string arg = argv[1];
                arg += " ";
                arg += argv[2];
                arg += " ";
                stringstream ss(arg);
                ss >> n;
                ss >> d;
                if(ss.eof() || ss.fail()) throw IOException();
                graph->graphGen(n, d, argv[3]);
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

    return 0;
}
