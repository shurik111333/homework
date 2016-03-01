#pragma once

#include "IStack.h"

template <typename T>
class StackPointer : public IStack<T>
{
public:
	StackPointer()
	{
		top = nullptr;
	}
	~StackPointer()
	{
		while (top)
		{
			pop();
		}
	}
	void push(T value)
	{
		StackElement *newElement = new StackElement(value, top);
		top = newElement;
	}
	T pop()
	{
		StackElement *elementForDelete = top;
		top = top->getNext();
		int result = elementForDelete->getValue();
		delete elementForDelete;
		return result;
	}
	T getTop() const
	{
		return top->getValue();
	}
	
	bool isEmpty() const
	{
		return top == nullptr;
	}
	
private:
	class StackElement
	{
	public:
		StackElement(T value, StackElement *next)
		{
			this->value = value;
			this->next = next;
		}
		T getValue() const
		{
			return value;
		}
		StackElement *getNext() const
		{
			return next;
		}
	private:
		T value;
		StackElement *next;
	};
	StackElement *top;
};
