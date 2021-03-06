#pragma once

template <typename T>
class IStack
{
public:
	virtual void push(T value) = 0;
	virtual T pop() = 0;
	virtual T getTop() const = 0;
	virtual bool isEmpty() const = 0;
	virtual void clear() = 0;
	
	virtual ~IStack()
	{}
};
