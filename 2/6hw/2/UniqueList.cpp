#include "UniqueList.h"

UniqueList::UniqueList():
    ListArray()
{}

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
