#pragma once

#include "IStack.h"

template <typename T>
class StackArray : public IStack<T>
{
public:
	StackArray(int size = defaultSize);
	~StackArray();
	
	void push(T value);
	T pop();
	T getTop() const;
	bool isEmpty() const;
	void clear();
	
private:
	int size;
	T *array;
	int top;
	const static int defaultSize = 10;
	
	void increaseStack();
};

template <typename T>
StackArray<T>::StackArray(int size)
    :size(size), array(new T[size]), top(0)
{}

template <typename T>
StackArray<T>::~StackArray()
{
	delete[] array;
}

template <typename T>
void StackArray<T>::push(T value)
{
	if (top >= size)
		increaseStack();
	array[top++] = value;
}

template <typename T>
T StackArray<T>::pop()
{
	return array[--top];
}

template <typename T>
T StackArray<T>::getTop() const
{
	return array[top - 1];
}

template <typename T>
bool StackArray<T>::isEmpty() const
{
	return top == 0;
}

template <typename T>
void StackArray<T>::clear()
{
	top = 0;
}

template <typename T>
void StackArray<T>::increaseStack()
{
	int newSize = size * 2;
	T *newArray = new T[newSize];
	for (int i = 0; i < size; i++)
	{
		newArray[i] = array[i];
	}
	size = newSize;
	delete[] array;
	array = newArray;
}