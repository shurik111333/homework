#pragma once

#include "ISort.h"

class HeapSort : public ISort
{
public:
	HeapSort();
	
	void sort(int *array, int length);
	
private:
	/**
	 * @brief Get right son of vertex in heap.
	 * @param vertex
	 * @return Return index of right son of vertex in heap.
	 */
	int rightSon(int vertex) const;
	
	/**
	 * @brief Get left son of vertex in heap.
	 * @param vertex
	 * @return Return index of left son of vertex in heap.
	 */
	int leftSon(int vertex) const;
	
	/**
	 * @brief Build heap in subtree with root vertex. Left and right subtrees must be a heap.
	 * @param vertex
	 * @param heap
	 * @param size
	 */
	void heapify(int vertex, int *heap, int size);
	
	/**
	 * @brief Build heap in input array
	 * @param size
	 * @param heap
	 */
	void buildHeap(int size, int *heap);
	
	/**
	 * @brief Start sorting in range [0; size - 1].
	 * @param inputArray
	 * @param size 
	 */
	void heapSort(int *inputArray, int size);
};
