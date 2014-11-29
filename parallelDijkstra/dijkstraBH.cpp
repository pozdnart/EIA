#include "dijkstraBH.hpp"

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
	double** distanceMatrix; // ??? private nebo shared
	double* currentDistances;
	MyGraph* graph;
	CBinaryHeap* binaryHeap;
	unsigned nodesCount;
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

	#pragma omp parallel for private(distanceMatrix, currentDistances, graph, binaryHeap, nodesCount, sourceNode, localLoopVarI, currentNodeIndex, targetNodeIndex, currentNodeDistance, newDistance, currentEdgeLength, neighborsArray, currentEdge, neighborsCount, node) num_threads(4)
	for (sourceNode = 0; sourceNode < m_Graph->size(); sourceNode++) {
		// inicializace tridnich promennych
		graph = m_Graph;
		nodesCount = graph->size();
		distanceMatrix = m_DistanceMatrix;
		currentDistances = new double[nodesCount];
		binaryHeap = new CBinaryHeap(nodesCount);

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
				delete node;
				// Relaxace sousedu
				neighborsArray = (*m_Graph)[currentNodeIndex]->edgesArray;
				neighborsCount = (*m_Graph)[currentNodeIndex]->neighborsCount;
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
				// distanceMatrix je sdilena promenna
				#pragma omp critical
				distanceMatrix[sourceNode][localLoopVarI] = currentDistances[localLoopVarI];
			}

		// uklid lokalnich
			delete [] currentDistances;
			delete binaryHeap;
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