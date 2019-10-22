#include <iostream>
#include "Heap.h"

using namespace std;
using namespace heap_space;

int main()
{
	Heap<int> h(5);
	int top;
	int length;

	h.insertElement(10);
	h.insertElement(15);
	h.insertElement(20);
	h.insertElement(25);
	h.insertElement(50);
	h.insertElement(66);
	h.insertElement(68);
	h.insertElement(77);
	h.insertElement(80);
	h.insertElement(99);
	h.insertElement(100);
	h.insertElement(110);

	h.print_heap();
	top = h.getMax();
	length = h.getHeapSize();

	cout << "\nTop of Heap: " << top;
	cout << "\nLength of Heap: " << length << endl << endl;

	h.deleteElement();

	h.print_heap();
	top = h.getMax();
	length = h.getHeapSize();

	cout << "\nTop of Heap: " << top;
	cout << "\nLength of Heap: " << length;

	return 0;
}
