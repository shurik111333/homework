#pragma once

#include <algorithm>
#include "emptyqueue.h"

using namespace std;

template <typename T>
class PriorityQueue
{
public:
	PriorityQueue();
	~PriorityQueue();

	/**
	 * @brief enqueue Insert new value in queue
	 * @param value
	 * @param priority
	 */
	void enqueue(T value, int priority);

	/**
	 * @brief dequeue Remove value with max priority
	 * @return Value with max priority
	 */
	T dequeue();

	/**
	 * @brief clear Remove all values from queue
	 */
	void clear();
	bool empty() const;

private:
	class Heap
	{
	public:
		Heap(int size = defaultSize);
		~Heap();

		/**
		 * @brief insert Add new value to heap
		 * @param value
		 * @param priority
		 */
		void insert(T value, int priority);

		/**
		 * @brief getMax Remove element with max priority
		 * @return Value with max priority
		 */
		T getMax();

		/**
		 * @brief getCount
		 * @return Number of elements in heap
		 */
		int getCount() const;

		/**
		 * @brief clear Remove all elements from heap
		 */
		void clear();

	private:
		const static int defaultSize = 10;
		int size;
		int count;

		struct Element
		{
			T value;
			int priority;
		};

		Element *heap;

		void increase();

		/**
		 * @brief heapify Restore heap after addition/deleting element
		 * @param vertex
		 */
		void heapify(const int vertex);
		int leftSon(const int vertex) const;
		int rightSon(int vertex) const;
	};

	Heap heap;
};

// PriorityQueue --------------------------------------

template <typename T>
PriorityQueue<T>::PriorityQueue()
{}

template <typename T>
PriorityQueue<T>::~PriorityQueue()
{}

template <typename T>
void PriorityQueue<T>::enqueue(T value, int priority)
{
	heap.insert(value, priority);
}

template <typename T>
T PriorityQueue<T>::dequeue()
{
	if (heap.getCount() == 0)
		throw EmptyQueue();
	return heap.getMax();
}

template <typename T>
void PriorityQueue<T>::clear()
{
	heap.clear();
}

template <typename T>
bool PriorityQueue<T>::empty() const
{
	return heap.getCount() == 0;
}

// PriorityQueue::Heap ------------------------------------

template <typename T>
PriorityQueue<T>::Heap::Heap(int size):
    size(size),
    count(0),
    heap(new Element[size])
{}

template <typename T>
PriorityQueue<T>::Heap::~Heap()
{
	delete[] heap;
}

template <typename T>
void PriorityQueue<T>::Heap::insert(T value, int priority)
{
	if (count == size)
		increase();
	heap[count++] = {value, priority};
	heapify(count / 2);
}

template <typename T>
T PriorityQueue<T>::Heap::getMax()
{
	swap(heap[0], heap[count - 1]);
	count--;
	heapify(1);
	return heap[count].value;
}

template <typename T>
int PriorityQueue<T>::Heap::getCount() const
{
	return count;
}

template <typename T>
void PriorityQueue<T>::Heap::clear()
{
	count = 0;
}

// private ----------------------------------------------

template <typename T>
void PriorityQueue<T>::Heap::increase()
{
	Element *newHeap = new Element[size * 2];
	for (int i = 0; i < getCount(); i++)
	{
		newHeap[i] = heap[i];
	}
	delete[] heap;
	heap = newHeap;
	size *= 2;
}

template <typename T>
void PriorityQueue<T>::Heap::heapify(int vertex)
{
	while (vertex > 0)
	{
		int maxVertex = vertex;
		if (leftSon(vertex) <= getCount() &&
		    heap[leftSon(vertex) - 1].priority > heap[maxVertex - 1].priority)
		{
			maxVertex = leftSon(vertex);
		}
		if (rightSon(vertex) <= getCount() &&
		    heap[rightSon(vertex) - 1].priority > heap[maxVertex - 1].priority)
		{
			maxVertex = rightSon(vertex);
		}
		if (maxVertex != vertex)
		{
			swap(heap[maxVertex - 1], heap[vertex - 1]);
			vertex = maxVertex;
		}
		else
		{
			vertex /= 2;
		}
	}
}

template <typename T>
int PriorityQueue<T>::Heap::leftSon(const int vertex) const
{
	return vertex * 2;
}

template <typename T>
int PriorityQueue<T>::Heap::rightSon(const int vertex) const
{
	return vertex * 2 + 1;
}
