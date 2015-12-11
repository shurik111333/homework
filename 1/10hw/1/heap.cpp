#include "tree.h"

const int defaultSize = 10;

struct Heap
{
    int size;
    int count;
    Tree **heap;

    Heap(int size = defaultSize)
        :size(size), count(0), heap(new Tree*[size])
    {}
};

Heap *getNewHeap()
{
    return new Heap();
}

Heap *getNewHeap(int size)
{
    return new Heap(size);
}

template <typename T>
void swap(T &a, T &b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

int rightSon(int vertex)
{
    return vertex * 2 + 1;
}

int leftSon(int vertex)
{
    return vertex * 2;
}

void heapify(int vertex, Heap *heap)
{
    while (vertex > 0)
    {
        int maxVertex = vertex;
        if (leftSon(vertex) <= heap->count && getPriority(heap->heap[leftSon(vertex) - 1]) < getPriority(heap->heap[maxVertex - 1]))
        {
            maxVertex = leftSon(vertex);
        }
        if (rightSon(vertex) <= heap->count && getPriority(heap->heap[rightSon(vertex) - 1]) < getPriority(heap->heap[maxVertex - 1]))
        {
            maxVertex = rightSon(vertex);
        }
        if (maxVertex != vertex)
        {
            swap(heap->heap[maxVertex - 1], heap->heap[vertex - 1]);
            vertex = maxVertex;
        }
        else
        {
            vertex /= 2;
        }
    }
}

void increaseHeap(Heap *heap)
{
    heap->size *= 2;
    Tree **newHeap = new Tree*[heap->size];
    for (int i = 0; i < heap->count; i++)
    {
        newHeap[i] = heap->heap[i];
    }
    delete[] heap->heap;
    heap->heap = newHeap;
}

void addToHeap(Heap *heap, Tree *value)
{
    if (heap->size == heap->count)
        increaseHeap(heap);
    heap->heap[heap->count++] = value;
    heapify(heap->count / 2, heap);
}

int size(Heap *heap)
{
    return heap == nullptr ? 0 : heap->count;
}

Tree *getMin(Heap *heap)
{
    swap(heap->heap[0], heap->heap[--heap->count]);
    heapify(1, heap);
    return heap->heap[heap->count];
}

void deleteHeap(Heap *heap)
{
    delete[] heap->heap;
    delete heap;
}
