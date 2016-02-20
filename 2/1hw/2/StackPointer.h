#pragma once

#include "istack.h"

template <typename T>
class StackPointer : public IStack<T>
{
public:
	StackPointer()
	{
		this->top = nullptr;
	}
	~StackPointer()
	{
		while (this->top)
		{
			this->pop();
		}
	}
	void push(T value)
	{
		StackElement *newElement = new StackElement(value, this->top);
		this->top = newElement;
	}
	T pop()
	{
		
		StackElement *elementForDelete = this->top;
		this->top = this->top->getNext();
		int result = elementForDelete->getValue();
		delete elementForDelete;
		return result;
	}
	T getTop() const
	{
		return this->top->getValue();
	}
	
	bool isEmpty() const
	{
		return this->top == nullptr;
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
			return this->value;
		}
		StackElement *getNext() const
		{
			return this->next;
		}
	private:
		T value;
		StackElement *next;
	};
	StackElement *top;
};
