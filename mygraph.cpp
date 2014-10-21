#include "mygraph.hpp"
#include "edge.hpp"
#include "exception.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <random>
#include <limits>

using namespace std;

MyGraph::MyGraph()
{}

MyGraph::MyGraph(const string fileName) {
    load(fileName);
}

MyGraph::~MyGraph() {
    unsigned int size = nodes.size();
    for(unsigned int i = 0; i < size; ++i) {
        delete nodes.at(i);
    }
}

void MyGraph::load(const string fileName) {
    ifstream ifs(fileName.c_str());
    if(!ifs.is_open()) throw IOException();
    unsigned int n;
    ifs >> n;
    if(ifs.eof() || ifs.fail()) throw IOException();

    matrix = new double *[n];

    for(unsigned int i = 0; i < n; ++i) {
        nodes.push_back(new Node());
        matrix[i] = new double[n];
        matrix[i][0] = numeric_limits<double>::max();
    }

    while(true) {
        int u, v;
        double dist;
        ifs >> u >> v >> dist;
        if(ifs.eof())
            break;
        else if(ifs.fail())
            throw IOException();

        matrix[u][v] = dist;
        matrix[v][u] = dist;

        nodes.at(u)->addEdge(nodes.at(v), dist);
        nodes.at(v)->addEdge(nodes.at(u), dist);
    }
}

void MyGraph::graphGen(int n, double probability, const string fileName) {
    ofstream ofs(fileName.c_str());
    if(!ofs.is_open()) throw IOException();
    ofs << n << endl;

    srand((unsigned)time(NULL));

    for(int i = 0; i < n; ++i) {
        for(int j = i + 1; j < n; ++j) {
            double random = ((double)rand()/(double)RAND_MAX);
            if(random < probability) {
                ofs << i << " " << j << " " << ((double)rand()/(double)RAND_MAX) * 100 << endl;
            }
        }
    }
}

Node * MyGraph::operator[](unsigned int i) {
    return nodes.at(i);
}

unsigned int MyGraph::size() {
    return nodes.size();
}

double ** MyGraph::getMatrix() {
    return matrix;
}
