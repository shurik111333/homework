#include <myQueue.h>

struct QueueNode
{
    int value;
    QueueNode *next;

    QueueNode(int value)
    {
        this->value = value;
        this->next = nullptr;
    }
};

struct Queue
{
    QueueNode *first = nullptr;
    QueueNode *tail = nullptr;
};

Queue *getNewQueue()
{
    return new Queue;
}

bool isEmpty(Queue *queue)
{
    return queue->first == nullptr;
}

void push(Queue *queue, int value)
{
    QueueNode *newNode = new QueueNode(value);
    if (isEmpty(queue))
    {
        queue->first = newNode;
        queue->tail = newNode;
        return;
    }
    queue->tail->next = newNode;
    queue->tail = newNode;
}

int pop(Queue *queue)
{
    int result = queue->first->value;
    QueueNode *tmp = queue->first;
    queue->first = queue->first->next;
    if (queue->first == nullptr)
    {
        queue->tail = nullptr;
    }
    delete tmp;
    return result;
}

void removeQueue(Queue *queue)
{
    while (!isEmpty(queue))
        pop(queue);
    delete queue;
}
