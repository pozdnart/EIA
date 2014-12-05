#include "dijkstraBH.hpp"
#include <omp.h>

using namespace std;

CDijkstra::CDijkstra(MyGraph* graph) : m_Graph(graph) {
	int nodesCount = (int) m_Graph->size();

	m_DistanceMatrix = new double*[nodesCount];
	for (int i = 0; i < nodesCount; i++) {
		m_DistanceMatrix[i] = new double[nodesCount];
	}

	m_CurrentDistances = new double[nodesCount];
	m_BinaryHeap = new CBinaryHeap(nodesCount);
}

CDijkstra::~CDijkstra() {
	for (unsigned i = 0; i < m_Graph->size(); i++) {
		delete [] m_DistanceMatrix[i];
	}
	delete [] m_DistanceMatrix;

	delete [] m_CurrentDistances;
	delete m_BinaryHeap;
}

double** CDijkstra::CalculateDistanceMatrix() {
	// kopii tridnich promennych
	double** distanceMatrix = m_DistanceMatrix;
	double* currentDistances;
	MyGraph* graph = m_Graph;
	CBinaryHeap* binaryHeap;
	unsigned nodesCount = m_Graph->size();
	// ridici promenna cyklu
	unsigned sourceNode;
	unsigned localLoopVarI;
	// lokalni promenne puvodni metody runDijkstraFrom
	unsigned currentNodeIndex, targetNodeIndex;
	double currentNodeDistance, newDistance;
	double currentEdgeLength;
	Edge** neighborsArray;
	Edge* currentEdge;
	unsigned neighborsCount;
	TBHNode* node;
	// inicializace vlakna
	bool initialized = false;

	#pragma omp parallel for firstprivate(initialized, graph, nodesCount, distanceMatrix) private(currentDistances, binaryHeap, sourceNode, localLoopVarI, currentNodeIndex, targetNodeIndex, currentNodeDistance, newDistance, currentEdgeLength, neighborsArray, currentEdge, neighborsCount, node) num_threads(4) schedule(guided) 
	for (sourceNode = 0; sourceNode < nodesCount; sourceNode++) {
		// inicializace tridnich promennych
		if (!initialized) {
			initialized = true;
			binaryHeap = new CBinaryHeap(nodesCount);
			currentDistances = new double[nodesCount];
		}

		// samotny beh DA z aktualniho uzlu, puvodne (runDijkstraFrom)
			// prepareDistances()
			for (localLoopVarI = 0; localLoopVarI < nodesCount; localLoopVarI++) {
				currentDistances[localLoopVarI] = numeric_limits<double>::max();
			}
			currentDistances[sourceNode] = 0;
			// enqueueNodes()
			for (localLoopVarI = 0; localLoopVarI < nodesCount; localLoopVarI++) {
				binaryHeap->Insert(localLoopVarI, currentDistances[localLoopVarI]);
			}
			// hlavni cyklus
			while (binaryHeap->Size() != 0) {
				// Index a vzdalenost uzlu s nejniysi vzdalenosti od pocatecniho uzlu
				node = binaryHeap->ExtractMin();
				currentNodeIndex = node->index;
				currentNodeDistance = node->distance;
				// Relaxace sousedu
				neighborsArray = (*graph)[currentNodeIndex]->edgesArray;
				neighborsCount = (*graph)[currentNodeIndex]->neighborsCount;
				for (localLoopVarI = 0; localLoopVarI < neighborsCount; localLoopVarI++) {
					// Pokud jsme nasli kratsi cestu k nejakemu sousedovi, ulozime ji a sousedni uzel znovu vlozime do fronty s novou vzdalenosti
				   	currentEdge = neighborsArray[localLoopVarI];
					currentEdgeLength = currentEdge->dist;
					targetNodeIndex = currentEdge->targetIndex;

					if (currentDistances[targetNodeIndex] > currentNodeDistance + currentEdgeLength) {
						newDistance = currentNodeDistance + currentEdgeLength;
						binaryHeap->DecreaseKey(targetNodeIndex, newDistance);
						currentDistances[targetNodeIndex] = newDistance;
					}
				}
			}

		// ulozeni spoctenych vzdalenosti (puvodne storeCalculatedDistances)
			for (localLoopVarI = 0; localLoopVarI < nodesCount; localLoopVarI++) {
				#pragma omp critical
				distanceMatrix[sourceNode][localLoopVarI] = currentDistances[localLoopVarI];
			}
	}

	return m_DistanceMatrix;
}

void CDijkstra::runDijkstraFrom(const int& nodeIndex) {
	unsigned currentNodeIndex, targetNodeIndex;
	double currentNodeDistance, newDistance;
	double currentEdgeLength;

	Edge** neighborsArray;
	Edge* currentEdge;
	unsigned neighborsCount;

	TBHNode* node;

	prepareDistances(nodeIndex);
	enqueueNodes();

	while (m_BinaryHeap->Size() != 0) {
		// Index a vzdalenost uzlu s nejniysi vzdalenosti od pocatecniho uzlu
		node = m_BinaryHeap->ExtractMin();
		currentNodeIndex = node->index;
		currentNodeDistance = node->distance;
		delete node;

		// Relaxace sousedu
		neighborsArray = (*m_Graph)[currentNodeIndex]->edgesArray;
		neighborsCount = (*m_Graph)[currentNodeIndex]->neighborsCount;
		for (unsigned i = 0; i < neighborsCount; i++) {
			// Pokud jsme nasli kratsi cestu k nejakemu sousedovi, ulozime ji a sousedni uzel znovu vlozime do fronty s novou vzdalenosti
		   	currentEdge = neighborsArray[i];
			currentEdgeLength = currentEdge->dist;
			targetNodeIndex = currentEdge->targetIndex;

			if (m_CurrentDistances[targetNodeIndex] > currentNodeDistance + currentEdgeLength) {
				
				newDistance = currentNodeDistance + currentEdgeLength;
				m_BinaryHeap->DecreaseKey(targetNodeIndex, newDistance);
				m_CurrentDistances[targetNodeIndex] = newDistance;
			}
		}
	}
}

void CDijkstra::prepareDistances(const int& nodeIndex) {
	for (unsigned i = 0; i < m_Graph->size(); i++) {
		m_CurrentDistances[i] = numeric_limits<double>::max();
	}

	m_CurrentDistances[nodeIndex] = 0;
}

void CDijkstra::enqueueNodes() {
	for (unsigned i = 0; i < m_Graph->size(); i++) {
		m_BinaryHeap->Insert(i, m_CurrentDistances[i]);
	}
}

void CDijkstra::storeCalculatedDistances(const unsigned& nodeIndex) {
	for (unsigned i = 0; i < m_Graph->size(); i++) {
		m_DistanceMatrix[nodeIndex][i] = m_CurrentDistances[i];
	}
}

void CDijkstra::printResult() const {
	for (unsigned i = 0; i < m_Graph->size(); i++) {
		for (unsigned j = i + 1; j < m_Graph->size(); j++) {
			cout << i << ' ' << j << ' ' << m_DistanceMatrix[i][j] << endl;
		}
	}
}