#include "QSort.h"
#include <algorithm>

QSort::QSort()
{}

void QSort::sort(int *array, int length)
{
	qSort(array, 0, length - 1);
}

void QSort::qSort(int *array, int left, int right)
{
	int i = left;
	int j = right;
	int m = array[(left + right) / 2];
	while (i < j)
	{
		while (array[i] < m)
			i++;
		while (array[j] > m)
			j--;
		if (i <= j)
		{
			std::swap(array[i], array[j]);
			i++;
			j--;
		}
	}
	if (i < right)
		qSort(array, i, right);
	if (j > left)
		qSort(array, left, j);
}
