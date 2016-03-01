#pragma once

#include "IStack.h"

template <typename T>
class StackPointer : public IStack<T>
{
public:
	StackPointer();
	~StackPointer();
	
	void push(T value);
	T pop();
	T getTop() const;	
	bool isEmpty() const;
	
private:
	class StackElement
	{
	public:
		StackElement(T value, StackElement *next);
		
		T getValue() const;
		StackElement *getNext() const;
		
	private:
		T value;
		StackElement *next;
	};
	StackElement *top;
};

//StackPointer----------------------------------------------------

template <typename T>
StackPointer<T>::StackPointer()
{
	top = nullptr;
}

template <typename T>
StackPointer<T>::~StackPointer()
{
	while (top)
	{
		pop();
	}
}

template <typename T>
void StackPointer<T>::push(T value)
{
	StackElement *newElement = new StackElement(value, top);
	top = newElement;
}

template <typename T>
T StackPointer<T>::pop()
{
	StackElement *elementForDelete = top;
	top = top->getNext();
	T result = elementForDelete->getValue();
	delete elementForDelete;
	return result;
}

template <typename T>
T StackPointer<T>::getTop() const
{
	return top->getValue();
}

template <typename T>
bool StackPointer<T>::isEmpty() const
{
	return top == nullptr;
}

//StackPointer::StackElement----------------------------------------------

template <typename T>
StackPointer<T>::StackElement::StackElement(T value, StackElement *next)
{
	this->value = value;
	this->next = next;
}

template <typename T>
T StackPointer<T>::StackElement::getValue() const
{
	return value;
}

template <typename T>
typename StackPointer<T>::StackElement *StackPointer<T>::StackElement::getNext() const
{
	return next;
}
