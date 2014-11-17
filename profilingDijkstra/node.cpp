#include "node.hpp"
#include "edge.hpp"

Node::Node(unsigned& ind) : index(ind) {}

Node::~Node() {
    unsigned int size = edges.size();
    for(unsigned int i = 0; i < size; ++i) {
        delete edges[i];
    }

    delete [] edgesArray;
}

void Node::addEdge(Node * node, double dist) {
    edges.push_back(new Edge(node, dist));
}

const unsigned& Node::getIndex() const {
	return index;
}

vector<Edge*> Node::expand() {
    return edges;
}

void Node::transformVectorToArray() {
	edgesArray = new Edge*[edges.size()];
	for(unsigned int i = 0; i < edges.size(); ++i) {
        edgesArray[i] = edges[i];
    }
    neighborsCount = edges.size();	
}