#include "ListArray.h"

ListArray::ListArray()
    :size(minSize), count(0), array(new int[size])
{}

ListArray::~ListArray()
{
	delete[] array;
}

void ListArray::insert(int value, int index)
{
	if (count == size)
		increaseList();
	for (int i = count; i > index; i--)
	{
		array[i] = array[i - 1];
	}
	array[index] = value;
	count++;
}

void ListArray::remove(int value) throw (NonexistentElementException)
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

int ListArray::findElementId(int value) const
{
	int i = 0;
	for (i = 0; i < count; i++)
	{
		if (array[i] == value)
			break;
	}
	return i == count ? -1 : i;
}

int ListArray::operator [](const int index) const throw (out_of_range)
{
	if (index < 0 || index >= count)
		throw out_of_range("Index out of range");
	return array[index];
}

void ListArray::increaseList()
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

int ListArray::length() const
{
	return count;
}
