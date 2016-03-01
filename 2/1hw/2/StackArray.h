#pragma once

#include "IStack.h"

template <typename T>
class StackArray : public IStack<T>
{
public:
	StackArray(int size = defaultSize)
	{
		this->size = size;
		this->array = new T[this->size];
		this->top = 0;
	}
	
	~StackArray()
	{
		delete[] array;
	}
	
	void push(T value)
	{
		if (top >= size)
			increaseStack();
		array[top++] = value;
	}
	
	T pop()
	{
		return array[--top];
	}
	
	T getTop() const
	{
		return array[top - 1];
	}
	
	bool isEmpty() const
	{
		return top == 0;
	}
	
private:
	T *array;
	int size;
	int top;
	const static int defaultSize = 10;
	
	void increaseStack()
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
	
};
