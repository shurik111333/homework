#include "ListArray.h"

ListArray::ListArray(int size)
{
	this->size = size;
	count = 0;
	array = new int[size];
}

ListArray::~ListArray()
{
	delete[] array;
}

void ListArray::insert(int value, int index)
{
	if (getCount() == size)
		increaseList();
	for (int i = getCount(); i > index; i--)
	{
		array[i] = array[i - 1];
	}
	array[index] = value;
	count++;
}

bool ListArray::remove(int value)
{
	int index = findElementId(value);
	if (index == -1)
		return false;
	for (int j = index + 1; j < getCount(); j++)
	{
		array[j - 1] = array[j];
	}
	count--;
	return true;
}

int ListArray::findElementId(int value) const
{
	int i = 0;
	for (i = 0; i < getCount(); i++)
	{
		if (array[i] == value)
			break;
	}
	return i == getCount() ? -1 : i;
}

int ListArray::operator [](const int index) const
{
	return array[index];
}

void ListArray::increaseList()
{
	int *newArray = new int[size * 2];
	for (int i = 0; i < getCount(); i++)
	{
		newArray[i] = array[i];
	}
	delete[] array;
	size *= 2;
	array = newArray;
}

int ListArray::getCount() const
{
	return count;
}