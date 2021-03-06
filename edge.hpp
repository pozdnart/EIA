// edge.hpp
#ifndef EDGE_HPP
#define EDGE_HPP

class Node;

/**
 * Hrana v grafu.
 */
class Edge {
public:
    /**
     * @param node Cilovy uzel.
     * @param dist Velikost hrany.
     */
    Edge(Node * node, double dist);

    /**
     * @return Velikost hrany.
     */
    double & distance();

    /**
     * @return Cilovy uzel.
     */
    Node & getTarget();
private:
    double dist;
    Node * target;
};

#endif
