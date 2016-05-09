#pragma once

#include "ListArray.h"

using namespace std;

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

		const char *what() const noexcept
		{
			return message;
		}

	private:
		const char *message;
	};

	void insert(int value, int index) throw(ElementAlreadyExistException);
};
