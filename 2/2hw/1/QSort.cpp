#include "QSort.h"

QSort::QSort()
{}

void swap(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

void QSort::sort(int *array, int left, int right)
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
			swap(array[i], array[j]);
			i++;
			j--;
		}
	}
	if (i < right)
		sort(array, i, right);
	if (j > left)
		sort(array, left, j);
}
