#include "dijkstra.hpp"

using namespace std;

bool CPairComparator::operator()(const pair<int, double>& lhs, const pair<int, double>& rhs) const {
    return lhs.second > rhs.second;
}


CDijkstra::CDijkstra(MyGraph* graph) : m_Graph(graph) {
	int nodesCount = (int) m_Graph->size();

	m_DistanceMatrix = new double*[nodesCount];
	for (int i = 0; i < nodesCount; i++) {
		m_DistanceMatrix[i] = new double[nodesCount];
	}

	m_CurrentDistances = new double[nodesCount];
}

CDijkstra::~CDijkstra() {
	for (unsigned i = 0; i < m_Graph->size(); i++) {
		delete [] m_DistanceMatrix[i];
	}
	delete [] m_DistanceMatrix;

	delete [] m_CurrentDistances;
}

double** CDijkstra::CalculateDistanceMatrix() {
	for (unsigned i = 0; i < m_Graph->size(); i++) {
		runDijkstraFrom(i);
		storeCalculatedDistances(i);
	}

	return m_DistanceMatrix;
}

void CDijkstra::runDijkstraFrom(const int& nodeIndex) {
	unsigned currentNodeIndex, targetNodeIndex;
	double currentNodeDistance, newDistance;
	vector<Edge*> neighbors;

	prepareDistances(nodeIndex);
	enqueueNodes();

	while (!m_PriorityQueue.empty()) {
		// Index a vzdalenost uzlu s nejniysi vzdalenosti od pocatecniho uzlu
		currentNodeIndex = m_PriorityQueue.top().first;
		currentNodeDistance = m_PriorityQueue.top().second;
		m_PriorityQueue.pop();

		// STL prioritni fronta neumi decrease_key, proto se v ni mohou nachazet jiz neplatne vzdalenosti
		// (pri nalezeni kratsi cesty se uzel prida do fronty znovu)
		if (m_CurrentDistances[currentNodeIndex] < currentNodeDistance) {
			continue;
		}

		neighbors = (*m_Graph)[currentNodeIndex]->expand();
		for (vector<Edge*>::const_iterator edgeIt = neighbors.begin(); edgeIt != neighbors.end(); edgeIt++) {
			// Pokud jsme nasli kratsi cestu k nejakemu sousedovi, ulozime ji a sousedni uzel znovu vlozime do fronty s novou vzdalenosti
			targetNodeIndex = (*edgeIt)->getTarget().getIndex();
			if (m_CurrentDistances[targetNodeIndex] > currentNodeDistance + (*edgeIt)->distance()) {
				newDistance = currentNodeDistance + (*edgeIt)->distance();
				m_CurrentDistances[targetNodeIndex] = newDistance;
				m_PriorityQueue.push(pair<int, double>(targetNodeIndex, newDistance));
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
		m_PriorityQueue.push(pair<int, double>(i, m_CurrentDistances[i]));
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
