#include "mygraph.hpp"
#include "exception.hpp"
#include <memory>
#include <iostream>
#include <sstream>

using namespace std;

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
