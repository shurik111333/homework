#pragma once

#include "ListArray.h"

using namespace std;

/// Implements list on array, which contains only different elements
class UniqueList : public ListArray
{
public:
	UniqueList();
	~UniqueList()
	{}

	class ElementAlreadyExistException : exception
	{
	public:
		ElementAlreadyExistException():
		    message("Element already exist")
		{}
		ElementAlreadyExistException(const char *msg):
		    message(msg)
		{}
		~ElementAlreadyExistException()
		{
			delete message;
		}

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
	void insert(int value, int index) throw(ElementAlreadyExistException);
};
