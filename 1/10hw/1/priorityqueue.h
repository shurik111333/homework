#pragma once

#include "tree.h"

struct PriorityQueue;

PriorityQueue *getNewQueue();

bool isEmpty(PriorityQueue *queue);

void push(PriorityQueue *queue, Tree *value);

Tree *pop(PriorityQueue *queue);

int size(PriorityQueue *queue);

void deleteQueue(PriorityQueue *queue);
