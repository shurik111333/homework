#include "UniqueList.h"

UniqueList::UniqueList():
    size(minSize),
    count(0),
    array(new int[size])
{}

UniqueList::~UniqueList()
{
	delete[] array;
}

void UniqueList::insert(int value, int index) throw(ElementAlreadyExistException)
{
	if (count == size)
		increaseList();
	if (findElementId(value) != -1)
		throw ElementAlreadyExistException();
	for (int i = count; i > index; i--)
	{
		array[i] = array[i - 1];
	}
	array[index] = value;
	count++;
}

void UniqueList::remove(int value) throw(NonexistentElementException)
{
	int index = findElementId(value);
	if (index == -1)
		throw NonexistentElementException();
	for (int j = index + 1; j < count; j++)
	{
		array[j - 1] = array[j];
	}
	count--;
}

int UniqueList::findElementId(int value) const noexcept
{
	int i = 0;
	for (i = 0; i < count; i++)
	{
		if (array[i] == value)
			break;
	}
	return i == count ? -1 : i;
}

int UniqueList::operator [](const int index) const throw(std::out_of_range)
{
	if (index >= 0 && index < count)
		return array[index];
	throw out_of_range("Out of range");
}

void UniqueList::increaseList() noexcept
{
	int *newArray = new int[size * 2];
	for (int i = 0; i < count; i++)
	{
		newArray[i] = array[i];
	}
	delete[] array;
	size *= 2;
	array = newArray;
}

int UniqueList::length() const noexcept
{
	return count;
}
