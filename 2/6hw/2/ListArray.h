#pragma once

#include <stdexcept>
#include "IList.h"

using std::exception;
using std::out_of_range;

/// Implements list on array
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

	/**
	 * @brief insert Insert element in list
	 * @param index Position for insert
	 */
	void insert(int value, int index);
	void remove(int value) throw (NonexistentElementException);
	/**
	 * @brief findElementId Find element in list
	 * @return Return position of value, or -1 if value does not exist
	 */
	int findElementId(int value) const;
	int operator [](const int index) const throw (out_of_range);
	int length() const;

protected:
	/// Current size of array
	int size;
	/// Number of elements in list
	int count;
	int *array;
	const static int minSize = 5;

	void increaseList();
};
