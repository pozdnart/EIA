#ifndef CDIJKSTRA_HPP
#define CDIJKSTRA_HPP

#include "mygraph.hpp"
#include "edge.hpp"
#include <queue>
#include <limits>
#include <vector>
#include <iostream>

using namespace std;

struct CPairComparator {
	bool operator()(const pair<int, double>& lhs, const pair<int, double>& rhs) const;
};

// Dijkstruv algoritmus (DA)
class CDijkstra {
public:
	// Prevze vstupni graf, alokuje distancni matici, inicializuje frontu
	CDijkstra(MyGraph* graph);

	// Uklidi
	~CDijkstra();

	// Spocte vzdalenosti mezi vsemi dvojicemi uzlu a vypise distancni matici
	void CalculateDistanceMatrix();

private:
	// Distancni matice
	double** m_DistanceMatrix;
	// Vzdalenosti uzlu pro jeden beh DA
	double* m_CurrentDistances;
	// Vstupni graf
	MyGraph* m_Graph;
	// Prioritni fronta pro beh DA
	priority_queue<pair<int, double>, vector<pair<int, double> >, CPairComparator > m_PriorityQueue;

	// Spusti Dijkstruv algoritmus z uzlu s danym indexem
	void runDijkstraFrom(const int& nodeIndex);

	// Inicializuje pole m_CurrentDistances pred behem DA (nastavi vzdalenost pocatecniho uzlu na 0, zbytek na max double)
	void prepareDistances(const int& nodeIndex);

	// Vlozi do prioritni fronty vsechny uzly (dvojice <index_uzlu, vzdalenost>)
	void enqueueNodes();

	// Ulozi vzdalenosti spoctene z jednoho uzlu spoctene v ramci jedne iteraci DA
	void storeCalculatedDistances(const unsigned& nodeIndex);

	// Vypise vyslednou distancni matici na stdout
	void printResult() const;
};

#endif 
