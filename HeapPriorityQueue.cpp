#include <iostream>
#include <fstream>
#include "Heap.h"

using namespace std;
using namespace heap_space;

void process_order();

ifstream inf;
Heap<int> h(100);

int main()
{
	int num = 0;
	int priority = 0;
	int top = 0;
	int length = 0;
	char ch = 0;

	inf.open("HeapPriorityNbrs.dat");

	if (!inf) {
		cout << "Error opening file!";
		return 0;
	}

	inf >> num;
	inf >> ch;
	inf >> priority;

	h.insertElement(priority, num);

	while (inf >> num) {
		inf >> ch;
		inf >> priority;

		h.insertElement(priority, num);
	}

	length = h.getHeapSize();
	h.print_heap();

	cout << "\nHeap size: " << length;

	cout << endl;

	inf.close();

	return 0;
}

void process_order() {

}
