#pragma once

class ISort
{
public:
	virtual void sort(int *array, int left, int right) = 0;
};