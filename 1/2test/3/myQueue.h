#pragma once

struct Queue;

Queue *getNewQueue();

bool isEmpty(Queue *queue);

void push(Queue *queue, int value);

int pop(Queue *queue);

void removeQueue(Queue *queue);
