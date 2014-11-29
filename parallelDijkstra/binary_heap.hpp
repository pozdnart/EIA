#include <utility>
#include <iostream>

using namespace std;

struct TBHNode {
	int index;
	double distance;

	TBHNode(const int& i, const double& dist) : index(i), distance(dist) {}
};

class CBinaryHeap {
	public:
		CBinaryHeap(const int& size);
		~CBinaryHeap();
		void Insert(const int& index, const double& distance);
		const TBHNode* GetMin();
		TBHNode* ExtractMin();
		int Size() const;
		void DebugPrint() const;
		// Tato metoda pracuje s indexem uzlu v grafu, NE s indexem uzlu v halde !!!
		void DecreaseKey(const int& graphNodeIndex, const double& newDistance);
		double GetNodeDistance(const int& graphNodeIndex) const;
	private:
		int m_CurrentSize;
		int* m_NodePositions;
		TBHNode** m_Heap;

		int getParentIndex(const int& nodeIndex) const;
		int getLeftChildIndex(const int& nodeIndex) const;
		int getRightChildIndex(const int& nodeIndex) const;
		void heapify(const int& nodeIndex);
};