#include "node.hpp"
#include "edge.hpp"

Node::~Node() {
    unsigned int size = edges.size();
    for(unsigned int i = 0; i < size; ++i) {
        delete edges[i];
    }
}

void Node::addEdge(Node * node, double dist) {
    edges.push_back(new Edge(node, dist));
}

vector<Edge*> Node::expand() {
    return edges;
}
