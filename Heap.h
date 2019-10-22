#ifndef HEAP_H
#define HEAP_H

#include <assert.h>

namespace heap_space {
	template<typename ET>
	class Heap {
	public:
		Heap(int cap) {
			heapArray = new ET[cap];
			size = 0;
			capacity = cap;

			for (int i = 0; i < cap; i++) {
				heapArray[i] = 0;
			}
		}


		void extraCapacity() {
			int extra = capacity * 2;
			capacity = extra;
			ET* another_heap = new ET[capacity];
			//ET* p = heapArray;

			for (int i = 0; i < capacity; i++) {
				another_heap[i] = 0;
			}

			for (int i = 1; i <= size; i++) {
				//assertion fails
				another_heap[i] = heapArray[i];
			}

			delete[] heapArray;

			heapArray = another_heap;
		}

		int getHeapSize() {
			return size;
		}

		int getMax() {
			return heapArray[1];
		}

		void insertElement(ET value) {
			int parent;
			int pos;

			if ((size + 2) == capacity) {
				extraCapacity();
			}

			//empty heap
			if (heapArray[1] == 0) {
				heapArray[1] = value;
				size++;
			}
			else { //non-empty heap
				heapArray[size + 1] = value;
				parent = (size + 1) / 2;

				//determine if val inserted is greater
				//than parent, if so then heapify up
				if (heapArray[size + 1] > heapArray[parent]) {
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
			int parent = (pos + 1) / 2;

			while (heapArray[pos] > heapArray[parent] && parent != 0) {
				swap(heapArray, pos, parent);
				pos = parent;
				parent = (pos + 1) / 2;
			}
		}

		void heapDown(int pos) {
			int largest = pos;
			int left = 2 * pos;
			int right = (2 * pos) + 1;

			if (left <= size && heapArray[largest] < heapArray[left]) {
				largest = left;
			}

			if (right <= size && heapArray[largest] < heapArray[right]) {
				largest = right;
			}

			if (largest != pos) {
				swap(heapArray, pos, largest);
				heapDown(largest);
			}

		}

		void swap(ET heap[], int pos, int parent) {
			int temp = heap[pos];
			heap[pos] = heap[parent];
			heap[parent] = temp;
		}

		void print_heap() {
			//print heap here

			for (int i = 1; i <= size; i++) {
				std::cout << heapArray[i] << " ";
			}
		}

	private:
		ET* heapArray;
		int size;
		int capacity;
	};
}

#endif