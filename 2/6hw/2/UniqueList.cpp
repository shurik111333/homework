#include "UniqueList.h"

UniqueList::UniqueList():
    ListArray()
{}

void UniqueList::insert(int value, int index) throw(ElementAlreadyExistException)
{
	if (findElementId(value) != -1)
		throw ElementAlreadyExistException();
	ListArray::insert(value, index);
}
