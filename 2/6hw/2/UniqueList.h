#pragma once

#include <stdexcept>

using namespace std;

class UniqueList
{
public:
	UniqueList();
	~UniqueList();

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

	void insert(int value, int index) throw(ElementAlreadyExistException);
	void remove(int value) throw(NonexistentElementException);
	/**
	 * @brief findElementId
	 * @param value
	 * @return Return id of element, or -1, if element does not exist
	 */
	int findElementId(int value) const noexcept;
	int operator [](const int index) const throw(std::out_of_range);
	int length() const noexcept;

private:
	int size;
	int count;
	int *array;
	const static int minSize = 5;

	void increaseList() noexcept;
};
