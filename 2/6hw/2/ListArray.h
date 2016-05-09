#pragma once

#include <stdexcept>
#include "IList.h"

using std::exception;
using std::out_of_range;

class ListArray : public IList<int>
{
public:
	ListArray();
	~ListArray();

	class NonexistentElementException : exception
	{
	public:
		NonexistentElementException():
		    message("Element doesn't exist")
		{}
		NonexistentElementException(const char *msg):
		    message(msg)
		{}

		const char *what() const noexcept
		{
			return message;
		}

	private:
		const char *message;
	};

	void insert(int value, int index);
	void remove(int value) throw (NonexistentElementException);
	int findElementId(int value) const;
	int operator [](const int index) const throw (out_of_range);
	int length() const;

protected:
	int size;
	int count;
	int *array;
	const static int minSize = 5;

	void increaseList();
};
