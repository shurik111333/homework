#pragma once

#include "ISort.h"

class BubbleSort : public ISort
{
public:
	BubbleSort();
	
	void sort(int *array, int length);
};
