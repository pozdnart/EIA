#include <iostream>
#include "binary_heap.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
	CBinaryHeap* bh = new CBinaryHeap(10);


	// bh->Insert(0, 5);
	// bh->DebugPrint();
	// bh->Insert(1, 7);
	// bh->DebugPrint();
	// bh->Insert(2, 3);
	// bh->DebugPrint();
	// bh->Insert(3, 2);
	// bh->DebugPrint();
	// bh->Insert(4, 0);
	// bh->DebugPrint();
	// bh->Insert(5, 1);
	// bh->DebugPrint();
	// bh->Insert(6, 5);
	// bh->DebugPrint();
	// bh->Insert(7, 9);
	// bh->DebugPrint();
	// bh->Insert(8, 8);
	// bh->DebugPrint();
	// bh->Insert(9, 6);
	// bh->DebugPrint();
	// cout << "-----------------------------------------------" << endl;

	// for (int i = 0; i < 10; i++) {
	// 	bh->DebugPrint();
	// 	TBHNode* node = bh->ExtractMin();
	// 	cout << node->index << " " << node->distance << endl;
	// 	delete node;
	// }
	// bh->DebugPrint();

	bh->Insert(0,4);
	bh->Insert(1,7);
	bh->Insert(2,9);
	bh->Insert(3,0);
	bh->Insert(4,4);
	bh->Insert(5,8);
	bh->Insert(6,1);
	bh->Insert(7,8);
	bh->Insert(8,10);
	bh->Insert(9,2);

	bh->DebugPrint();

	bh->DecreaseKey(8, 1);

	bh->DebugPrint();	

	bh->DecreaseKey(4, 2);
	bh->DecreaseKey(2, 0);

	bh->DebugPrint();

	cout << bh->GetNodeDistance(8) << endl;
	cout << bh->GetNodeDistance(0) << endl;



	for (int i = 0; i < 10; i++) {
		cout << bh->ExtractMin()->distance << endl;
	}

	delete bh;
	return 0;
}