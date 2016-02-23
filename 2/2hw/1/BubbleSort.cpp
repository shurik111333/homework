#include "BubbleSort.h"
#include <algorithm>

BubbleSort::BubbleSort()
{}

void BubbleSort::sort(int *array, int length)
{
	for (int i = 1; i < length; i++)
		for (int j = 0; j < i; j++)
			if (array[i] < array[j])
				std::swap(array[i], array[j]);
}
