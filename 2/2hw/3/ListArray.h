#pragma once

#include "IList.h"
#include "ListComparator.h"

class ListArray : public IList<int>
{
public:
	ListArray(int size = minSize);
	
	~ListArray();
	
	void insert(int value, int index);
	
	bool remove(int value);
	
	int findElementId(int value) const;
	
	int operator [](const int index) const;
	
	int getCount() const;
	
private:
	int size;
	int count;
	int *array;
	static const int minSize = 5;
	
	void increaseList();
};
