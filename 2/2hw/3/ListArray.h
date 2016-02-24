#pragma once

#include "IList.h"

class ListArray : public IList<int>
{
public:
	ListArray(int size = minSize);
	
	~ListArray();
	
	void insert(int value, int index);
	
	bool remove(int value);
	
	int findElementId(int value) const;
	
	int operator [](const int index) const;
	
	int count() const;
	
private:
	int size;
	int _count;
	int *array;
	static const int minSize = 5;
	
	void increaseList();
};
