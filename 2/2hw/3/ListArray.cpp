#include "ListArray.h"

ListArray::ListArray(int size)
{
	this->size = size;
	_count = 0;
	array = new int[size];
}

ListArray::~ListArray()
{
	delete[] array;
}

void ListArray::insert(int value, int index)
{
	if (count() == size)
		increaseList();
	for (int i = count(); i > index; i--)
	{
		array[i] = array[i - 1];
	}
	array[index] = value;
	_count++;
}

bool ListArray::remove(int value)
{
	int index = findElementId(value);
	if (index == -1)
		return false;
	for (int j = index + 1; j < count(); j++)
	{
		array[j - 1] = array[j];
	}
	_count--;
	return true;
}

int ListArray::findElementId(int value) const
{
	int i = 0;
	for (i = 0; i < count(); i++)
	{
		if (array[i] == value)
			break;
	}
	return i == count() ? -1 : i;
}

int ListArray::operator [](const int index) const
{
	return array[index];
}

void ListArray::increaseList()
{
	int *newArray = new int[size * 2];
	for (int i = 0; i < count(); i++)
	{
		newArray[i] = array[i];
	}
	delete[] array;
	size *= 2;
	array = newArray;
}

int ListArray::count() const
{
	return _count;
}