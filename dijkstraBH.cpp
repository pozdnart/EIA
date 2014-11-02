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

void CDijkstra::CalculateDistanceMatrix() {
	for (unsigned i = 0; i < m_Graph->size(); i++) {
		runDijkstraFrom(i);
		storeCalculatedDistances(i);
	}

	printResult();
}

void CDijkstra::runDijkstraFrom(const int& nodeIndex) {
	unsigned currentNodeIndex, targetNodeIndex;
	double currentNodeDistance, newDistance;
	vector<Edge*> neighbors;
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
		neighbors = (*m_Graph)[currentNodeIndex]->expand();
		for (vector<Edge*>::const_iterator edgeIt = neighbors.begin(); edgeIt != neighbors.end(); edgeIt++) {
			// Pokud jsme nasli kratsi cestu k nejakemu sousedovi, ulozime ji a sousedni uzel znovu vlozime do fronty s novou vzdalenosti
			targetNodeIndex = (*edgeIt)->getTarget().getIndex();
			if (m_CurrentDistances[targetNodeIndex] > currentNodeDistance + (*edgeIt)->distance()) {
				newDistance = currentNodeDistance + (*edgeIt)->distance();
				m_CurrentDistances[targetNodeIndex] = newDistance;
				m_BinaryHeap->DecreaseKey(targetNodeIndex, newDistance);
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