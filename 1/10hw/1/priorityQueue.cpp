#include "tree.h"
#include "heap.h"
#include <limits.h>

struct PriorityQueue
{
    Heap *heap;
};

PriorityQueue *getNewQueue()
{
    return new PriorityQueue{getNewHeap()};
}

void push(PriorityQueue *queue, Tree *value)
{
    addToHeap(queue->heap, value);
}

int size(PriorityQueue *queue)
{
    return queue == nullptr ? 0 : size(queue->heap);
}

bool isEmpty(PriorityQueue *queue)
{
    return queue == nullptr || size(queue->heap) == 0;
}

Tree *pop(PriorityQueue *queue)
{
    return getMin(queue->heap);
}

void deleteQueue(PriorityQueue *queue)
{
    while (!isEmpty(queue))
    {
        deleteTree(pop(queue));
    }
    deleteHeap(queue->heap);
    delete queue;
}
