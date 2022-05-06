#include "BinaryHeap.h"
#include <functional>

using namespace std;

int main() {
	BinaryHeap<int> heap = BinaryHeap<int>(greater<int>());
	heap.toss({15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1});
	cout << heap << endl;
	heap.fixHeap();
	cout << heap << endl;
	cout << heap.removeTop() << endl;
	cout << heap << endl;
}