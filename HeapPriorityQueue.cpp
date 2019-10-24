#include <iostream>
#include <fstream>
#include "Heap.h"

using namespace std;
using namespace heap_space;

void process_orders();

ifstream inf;
Heap<int> h(100);

int main()
{
	int num = 0;
	int priority = 0;
	int top = 0;
	int length = 0;
	int i = 0;
	int found_pos = 0;
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

	i = 1;

	while (inf >> num) {
		//after the first 100, process them
		if (i == 100) {
			process_orders();
		}

		//after the next 100, process them
		if (i == 200) {
			process_orders();
		}

		inf >> ch;
		inf >> priority;

		if (h.search_heap(priority, num, found_pos) == true) {
			h.update_key(priority, found_pos);
		}
		else {
			h.insertElement(priority, num);
		}
		i++;
	}

	process_orders();

	//length = h.getHeapSize();
	//h.print_heap();

	//cout << "\nHeap size: " << length;

	cout << endl;

	inf.close();

	return 0;
}

void process_orders() {
	HeapStruct<int> max;
	int process = 0;
	int print = 0;

	cout << "\n\nProcessing 50 requests (only printing 20): " << endl;
	max = h.getMax();
	h.deleteElement();
	cout << max.priority << "-" << max.value << "; ";
	process = 1;
	print = 1;

	//delete the first 50 requests
	while (process != 50) {
		max = h.getMax();
		h.deleteElement();

		//print only the first 20 requests
		if (print < 20) {
			cout << max.priority << "-" << max.value << "; ";
		}

		process++;
		print++;
	}
}
