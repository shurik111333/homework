#include "SortedSet.h"

SortedSet::SortedSet(int size)
{
	array = new ListComparator*[size];
	this->size = size;
	count = 0;
}

SortedSet::~SortedSet()
{
	delete[] array;
}

bool SortedSet::add(ListComparator *input)
{
	if (count == size)
		increaseArray();
	int newIndex = find(input);
	if (newIndex < count && *array[newIndex] == *input)
		return false;
	for (int i = count; i > newIndex; i--)
	{
		array[i] = array[i - 1];
	}
	array[newIndex] = input;
	count++;
	return true;
}

bool SortedSet::remove(ListComparator *input)
{
	int index = find(input);
	if (index == count || !(*array[index] == *input))
		return false;
	ListComparator *element = array[index];
	for (int i = index; i < count - 1; i++)
	{
		array[i] = array[i + 1];
	}
	count--;
	delete element;
	return true;
}

bool SortedSet::contains(ListComparator *input) const
{
	int index = find(input);
	return index < count && *array[index] == *input;
}

ListComparator *SortedSet::min() const
{
	return array[0];
}

ListComparator *SortedSet::max() const
{
	return array[count - 1];
}

void SortedSet::clear()
{
	for (int i = 0; i < count; i++)
	{
		delete array[i];
	}
	count = 0;
}

bool SortedSet::empty() const
{
	return count == 0;
}

void SortedSet::increaseArray()
{
	ListComparator **newArray = new ListComparator*[size * 2];
	for (int i = 0; i < count; i++)
	{
		newArray[i] = array[i];
	}
	delete[] array;
	array = newArray;
}

int SortedSet::find(ListComparator *input) const
{
	int i = 0;
	while (i < count && *array[i] < *input)
	{
		i++;
	}
	return i;
}