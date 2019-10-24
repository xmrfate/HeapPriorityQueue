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
		//default constructor
		Heap(int cap) {
			heapArray = new HeapStruct<ET>[cap];
			size = 0;
			capacity = cap;

			for (int i = 0; i < cap; i++) {
				heapArray[i].priority = 0;
				heapArray[i].value = 0;
			}
		}

		//method to add more memory
		void extraCapacity() {
			int extra = capacity * 2;
			capacity = extra;
			HeapStruct<ET>* another_heap = new HeapStruct<ET>[capacity];

			//initialize new heap to all zeros
			for (int i = 0; i < capacity; i++) {
				another_heap[i].priority = 0;
				another_heap[i].value = 0;
			}

			//copy values
			for (int i = 1; i <= size; i++) {
				another_heap[i].priority = heapArray[i].priority;
				another_heap[i].value = heapArray[i].value;
			}

			delete[] heapArray;

			//set original heap to new heap
			heapArray = another_heap;
		}

		//returns size of heap
		int getHeapSize() {
			return size;
		}

		//returns the struct that is the current max
		HeapStruct<ET> getMax() {
			return heapArray[1];
		}

		//inserts elements into heap
		void insertElement(int p, ET val) {
			int parent;
			int pos;

			//add more capacity if size is 2 away from cap
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

		//deletes current max
		void deleteElement() {
			int pos = 1;
			heapArray[pos] = heapArray[size];
			heapArray[size].priority = 0;
			heapArray[size].value = 0;

			//decrement size and heap current max
			//down to correct pos
			size--;
			heapDown(pos);
		}

		//method to heap a struct up
		void heapUp(int pos) {
			int parent = (pos) / 2;

			//while current priority is greater than parent, swap them
			while (heapArray[pos].priority > heapArray[parent].priority && parent != 0) {
				swap(heapArray, pos, parent);
				pos = parent;
				parent = (pos) / 2;
			}
		}

		//method heap a struct down
		void heapDown(int pos) {
			int largest = pos;
			int left = 2 * pos; //left child
			int right = (2 * pos) + 1; //right child

			if (left <= size && heapArray[largest].priority < heapArray[left].priority) {
				largest = left;
			}

			if (right <= size && heapArray[largest].priority < heapArray[right].priority) {
				largest = right;
			}

			//swap as long as largest does not equal current pos
			//if it is, we are done
			if (largest != pos) {
				swap(heapArray, pos, largest);
				heapDown(largest);
			}

		}

		//swap method for structs
		void swap(HeapStruct<ET> heap[], int pos, int parent) {
			int temp_p = heap[pos].priority;
			ET temp_v = heap[pos].value;

			heap[pos].priority = heap[parent].priority;
			heap[pos].value = heap[parent].value;

			heap[parent].priority = temp_p;
			heap[parent].value = temp_v;
		}

		//method to search a heap
		bool search_heap(int p, ET val, int& pos) {
			bool res = false;
			
			//continue searching until res is true or pos > size
			while (res == false && pos <= size) {
				if (heapArray[pos].priority == p && heapArray[pos].value == val) {
					res = true;
				}
				else {
					res = false;
				}

				pos++;
			}

			return res;
		}

		//update priority to value p
		void update_key(int p, int found_pos) {
			heapArray[found_pos].priority = p;
		}

		void print_heap() {
			//print heap here

			for (int i = 1; i <= size; i++) {
				std::cout << heapArray[i].priority << " " << heapArray[i].value << ", ";
			}
		}

	private:
		HeapStruct<ET>* heapArray;
		int size;
		int capacity;
	};
}

#endif