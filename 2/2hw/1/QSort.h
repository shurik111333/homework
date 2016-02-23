#pragma once

#include "ISort.h"

class QSort : public ISort
{
public:
	QSort();
	
	void sort(int *array, int length);
	
private:
	void qSort(int *array, int left, int right);
};

