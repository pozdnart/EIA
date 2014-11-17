#include "binary_heap.hpp"

CBinaryHeap::CBinaryHeap(const int& size) {
	m_Heap = new TBHNode*[size];

	m_NodePositions = new int[size];
	m_CurrentSize = 0;
}

CBinaryHeap::~CBinaryHeap() {
	for (int i = 0; i < m_CurrentSize; i++) {
		delete m_Heap[i];
	}
	delete [] m_Heap;
	delete [] m_NodePositions;
}

void CBinaryHeap::Insert(const int& index, const double& distance) {
	m_CurrentSize++;
	
	int position = m_CurrentSize - 1;
	while (position > 0 && m_Heap[getParentIndex(position)]->distance > distance) {
		m_Heap[position] = m_Heap[getParentIndex(position)];
		m_NodePositions[m_Heap[position]->index] = position;
		position = getParentIndex(position);
	}

	m_NodePositions[index] = position;
	m_Heap[position] = new TBHNode(index, distance);
}

const TBHNode* CBinaryHeap::GetMin() {
	return m_Heap[0];
}

TBHNode* CBinaryHeap::ExtractMin() {
	TBHNode* min = m_Heap[0];

	m_NodePositions[m_Heap[0]->index] = -1;
	m_NodePositions[m_Heap[m_CurrentSize - 1]->index] = 0;

	m_Heap[0] = m_Heap[m_CurrentSize - 1];
	m_CurrentSize--;
	if (m_CurrentSize > 0) {
		heapify(0);
	}

	return min;
}

int CBinaryHeap::Size() const {
	return m_CurrentSize;
}

void CBinaryHeap::DebugPrint() const {
	cout << "Binarni halda, prvku: " << m_CurrentSize << endl;
	cout << "Halda v poli: " << endl;
	for (int i = 0; i < m_CurrentSize; i++) {
		cout << "i-" << i << " Index: " << m_Heap[i]->index <<  " Distance: " << m_Heap[i]->distance << endl;
	}
	cout << "Pozice" << endl;
	for (int i = 0; i < 10; i++) {
		cout << "i-" << i << " " << m_NodePositions[i] << endl;
	}
}

void CBinaryHeap::DecreaseKey(const int& graphNodeIndex, const double& newDistance) {
	int nodeIndex = m_NodePositions[graphNodeIndex];
	TBHNode* temp;
	// nova vzdalenost neni nizsi
	if (m_Heap[nodeIndex]->distance < newDistance) {
		return;
	} else {
		m_Heap[nodeIndex]->distance = newDistance;
	}

	while (nodeIndex > 0 && m_Heap[getParentIndex(nodeIndex)]->distance > newDistance) {
		// Ulozeni novych indexu
		m_NodePositions[m_Heap[nodeIndex]->index] = getParentIndex(nodeIndex);
		m_NodePositions[m_Heap[getParentIndex(nodeIndex)]->index] = nodeIndex;
		// Prohozeni rodice se synem
		temp = m_Heap[nodeIndex];
		m_Heap[nodeIndex] = m_Heap[getParentIndex(nodeIndex)];
		m_Heap[getParentIndex(nodeIndex)] = temp;
		// Posun indexu na rodice
		nodeIndex = getParentIndex(nodeIndex);
	}
}

double CBinaryHeap::GetNodeDistance(const int& graphNodeIndex) const {
	return m_Heap[m_NodePositions[graphNodeIndex]]->distance;
}

int CBinaryHeap::getParentIndex(const int& nodeIndex) const {
	return (nodeIndex - 1) / 2;
}

int CBinaryHeap::getLeftChildIndex(const int& nodeIndex) const {
	return 2 * nodeIndex + 1;
}

int CBinaryHeap::getRightChildIndex(const int& nodeIndex) const {
	return 2 * nodeIndex + 2;
}

void CBinaryHeap::heapify(const int& nodeIndex) {
	int leftChildIndex, rightChildIndex, minIndex;
	TBHNode* temp;

	leftChildIndex = getLeftChildIndex(nodeIndex);
	rightChildIndex = getRightChildIndex(nodeIndex);

	if (leftChildIndex < m_CurrentSize && m_Heap[leftChildIndex]->distance < m_Heap[nodeIndex]->distance) {
		minIndex = leftChildIndex;
	} else {
		minIndex = nodeIndex;
	}

	if (rightChildIndex < m_CurrentSize && m_Heap[rightChildIndex]->distance < m_Heap[minIndex]->distance) {
		minIndex = rightChildIndex;
	}

	if (minIndex != nodeIndex) {
		m_NodePositions[m_Heap[nodeIndex]->index] = minIndex;
		m_NodePositions[m_Heap[minIndex]->index] = nodeIndex;
		
		temp = m_Heap[nodeIndex];
		m_Heap[nodeIndex] = m_Heap[minIndex];
		m_Heap[minIndex] = temp;

		heapify(minIndex);
	}
}
