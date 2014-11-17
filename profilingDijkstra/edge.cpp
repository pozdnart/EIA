#include "edge.hpp"
#include "node.hpp"

Edge::Edge(Node * node, double dist) {
    this->dist = dist;
    this->target = node;
    this->targetIndex = node->index;
}

double & Edge::distance() {
    return dist;
}

Node & Edge::getTarget() {
    return *target;
}
