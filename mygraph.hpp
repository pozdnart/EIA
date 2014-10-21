// mygraph.hpp
#ifndef MYGRAPH_HPP
#define MYGRAPH_HPP

#include <string>
#include <vector>
#include "node.hpp"

using namespace std;

/**
 * Graf, obsahuje vsechny uzly a umi i generovat graf do souboru.
 */
class MyGraph {
public:
    /**
     * Prazny graf.
     */
    MyGraph();

    /**
     * Pri vytvareni nacte graf ze souboru. Haze vyjimku IOException.
     * @param fileName Nazev souboru.
     */
    MyGraph(const string fileName);

    ~MyGraph();

    /**
     * Nacte graf ze souboru. Haze vyjimku IOException.
     * @param fileName Nazev souboru.
     */
    void load(const string fileName);

    /**
     * Vygeneruje graf do souboru. Vzdalenosti jsou maximalne 100.0 velike. Haze vyjimku IOException.
     * @param n Pocet uzlu.
     * @param probability pravdepodobnost, ze z nejakeho uzlu 'u' do uzlu 'v' povede hrana.
     * @param fileName Nazev souboru.
     */
    void graphGen(int n, double probability, const string fileName);

    /**
     * Operator []
     * @param i Index uzlu, ktery vraci.
     */
    Node * operator[](unsigned int i);

    /**
     * Pocet uzlu v grafu.
     * @return Pocet uzlu.
     */
    unsigned int size();
private:
    vector<Node*> nodes;
};

#endif
