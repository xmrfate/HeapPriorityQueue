#ifndef HEAP_H
#define HEAP_H

#include <assert.h>

namespace heap_space {
	template<typename ET>
	struct HeapStruct {
		int priority;
		ET value;
	};

	template<typename ET>
	class Heap {
	public:
		Heap(int cap) {
			heapArray = new HeapStruct<ET>[cap];
			size = 0;
			capacity = cap;

			for (int i = 0; i < cap; i++) {
				heapArray[i].priority = 0;
				heapArray[i].value = 0;
			}
		}


		void extraCapacity() {
			int extra = capacity * 2;
			capacity = extra;
			HeapStruct<ET>* another_heap = new HeapStruct<ET>[capacity];
			//ET* p = heapArray;

			for (int i = 0; i < capacity; i++) {
				another_heap[i].priority = 0;
				another_heap[i].value = 0;
			}

			for (int i = 1; i <= size; i++) {
				//assertion fails
				another_heap[i].priority = heapArray[i].priority;
				another_heap[i].value = heapArray[i].value;
			}

			delete[] heapArray;

			heapArray = another_heap;
		}

		int getHeapSize() {
			return size;
		}

		ET getMax() {
			return heapArray[1].value;
		}

		void insertElement(int p, ET val) {
			int parent;
			int pos;

			if ((size + 2) == capacity) {
				extraCapacity();
			}

			//empty heap
			if (heapArray[1].priority == 0 && heapArray[1].value == 0) {
				heapArray[1].priority = p;
				heapArray[1].value = val;
				size++;
			}
			else { //non-empty heap
				heapArray[size + 1].priority = p;
				heapArray[size + 1].value = val;
				parent = (size + 1) / 2; //size+1

				//determine if val inserted is greater
				//than parent, if so then heapify up
				if (heapArray[size + 1].priority > heapArray[parent].priority) {
					pos = size + 1;
					heapUp(pos);
				}

				size++;
			}
		}

		void deleteElement() {
			int pos = 1;
			heapArray[pos] = heapArray[size];
			heapArray[size] = 0;

			size--;
			heapDown(pos);
			heapDown(pos);
		}

		void heapUp(int pos) {
			int parent = (pos) / 2;

			while (heapArray[pos].priority > heapArray[parent].priority && parent != 0) {
				swap(heapArray, pos, parent);
				pos = parent;
				parent = (pos) / 2;
			}
		}

		void heapDown(int pos) {
			int largest = pos;
			int left = 2 * pos;
			int right = (2 * pos) + 1;

			if (left <= size && heapArray[largest].priority < heapArray[left].priority) {
				largest = left;
			}

			if (right <= size && heapArray[largest].priority < heapArray[right].priority) {
				largest = right;
			}

			if (largest != pos) {
				swap(heapArray, pos, largest);
				heapDown(largest);
			}

		}

		void swap(HeapStruct<ET> heap[], int pos, int parent) {
			int temp_p = heap[pos].priority;
			ET temp_v = heap[pos].value;

			heap[pos].priority = heap[parent].priority;
			heap[pos].value = heap[parent].value;

			heap[parent].priority = temp_p;
			heap[parent].value = temp_v;
		}

		void print_heap() {
			//print heap here

			for (int i = 1; i <= size; i++) {
				std::cout << heapArray[i].priority << " " << heapArray[i].value << std::endl;
			}
		}

	private:
		HeapStruct<ET>* heapArray;
		int size;
		int capacity;
	};
}

#endif