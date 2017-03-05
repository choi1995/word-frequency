/*--- max_heap.cpp -----------------------------------------------
  This file implements hax_heap.hpp member functions.
-------------------------------------------------------------------------*/

#include "max_heap.hpp"
#include <stdexcept>

max_heap::max_heap(int n){
	data = new text_item[n];
	numItems = 0;
	max_capacity = n;
}

max_heap::~max_heap()
{ 
	delete [] data;
}

bool max_heap::empty() const {
	return (numItems == 0);
}
bool max_heap::full() const {
	return (numItems == max_capacity);
}

int max_heap::size() const {
	return numItems;
}	

text_item& max_heap::top() {
	if (empty()) {
		throw std::logic_error("Heap is empty, can't access top!");
	}
	return data[0];
}

text_item& max_heap::bottom() {
    if (empty()) {
        throw std::logic_error("Heap is empty, can't access top!");
    }
    return data[size()-1];
}

//--- You must comple the following functions: 


text_item max_heap::delete_max() {
	if (empty()) {
		throw std::logic_error("Cannot delete, heap is empty!");
	} else {
        text_item returnVal = data[0];
        
        if(numItems != 1){
            data[0] = data[numItems-1];
        }
        numItems--;
        swap_down(0);

		return returnVal;
	}
}

void max_heap::swap_down(int i) {
    int leftChild = 2*i+1;
    int rightChild = 2*i+2;
    
    if(i >= numItems || i < 0) return;
    
    int minIndex = i;
    
    if(leftChild < numItems && data[leftChild].freq > data[minIndex].freq)
        minIndex = leftChild;
    if(rightChild < numItems && data[rightChild].freq > data[minIndex].freq)
        minIndex = rightChild;
    
    if(minIndex != i){
        text_item temp = data[minIndex];
        data[minIndex] = data[i];
        data[i] = temp;
        swap_down(minIndex);
    }
}

void max_heap::insert(const text_item & item) {
	if (full()) {
		throw std::logic_error("Cannot insert, heap array is full!");
	} else {
        // inserting a new item at index = numItem, incrementing following that operation
		data[numItems++] = item;
        swap_up(numItems-1);
	}
}

void max_heap::swap_up(int i) {
    int parent = (i-1)/2;
    
    if(i >= numItems || i <= 0 ) return;
    
    // checking if the parent index is in the array; comparing the word frequency between
    // the parent and the child
    if(parent >= 0 && data[parent].freq < data[i].freq) {
        text_item temp = data[parent];
        data[parent] = data[i];
        data[i] = temp;
        swap_up(parent);
    }
}
