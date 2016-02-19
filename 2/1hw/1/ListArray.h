#pragma once

#include "IList.h"

class ListArray : public IList<int>
{
public:
	ListArray();
	
	~ListArray();
	
	void insert(int value, int index);
	
	bool remove(int value);
	
	int findElementId(int value) const;
	
	int operator [](const int index) const;
	
private:
	int size;
	int count;
	int *array;
	const int minSize = 5;
	
	void increaseList();
};
