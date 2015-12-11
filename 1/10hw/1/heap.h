#pragma once

struct Heap;

Heap *getNewHeap();

Heap *getNewHeap(int size);

void addToHeap(Heap *heap, Tree *value);

int size(Heap *heap);

Tree *getMin(Heap *heap);

void deleteHeap(Heap *heap);
