#pragma once

#include "ISort.h"

class HeapSort : public ISort
{
public:
	HeapSort();
	
	void sort(int *array, int length);
	
private:
	int rightSon(int vertex) const;
	
	int leftSon(int vertex) const;
	
	void heapify(int vertex, int *heap, int size);
	
	void buildHeap(int size, int *heap);
	
	void heapSort(int *inputArray, int size);
};
