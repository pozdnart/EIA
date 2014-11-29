// node.hpp
#ifndef NODE_HPP
#define NODE_HPP

#include <vector>

using namespace std;

class Edge;

/**
 * Uzel grafu, obsahuje hrany, ktere z nej vedou.
 */
class Node {
public:
    Node(unsigned& ind);

    ~Node();
    /**
     * Prida hranu k uzlu.
     * @param node Cilovu uzel.
     * @param dist Velikost hrany.
     */
    void addEdge(Node * node, double dist);

    const unsigned& getIndex() const;

    /**
     * @return Hrany vedouci z uzlu.
     */
    vector<Edge*> expand();

    void transformVectorToArray();
    // Zpristupneni polozky ze vnejsku
    const unsigned index; 
    unsigned neighborsCount;   
    Edge** edgesArray;
private:
    vector<Edge*> edges;

    //const unsigned index;
};

#endif
