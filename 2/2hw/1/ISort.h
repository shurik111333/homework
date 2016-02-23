#pragma once

/**
 * @brief Interface for array sorter
 */
class ISort
{
public:
	virtual void sort(int *array, int length) = 0;
	
	virtual ~ISort()
	{}
};