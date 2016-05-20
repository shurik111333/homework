#pragma once

#include <algorithm>
#include <QList>
#include "comparator.h"
#include "bubbleSorter.h"

using std::swap;

/// Sorts list of objects with input comparator. Use algorithm bubble sort.
template <typename T>
class BubbleSorter
{
public:
	BubbleSorter()
	{}

	/// @brief Sort elements in the list.
	void sort(QList<T> &array, Comparator<T> *cmp) const;
};

template <typename T>
void BubbleSorter<T>::sort(QList<T> &array, Comparator<T> *cmp) const
{
	int len = array.size();
	for (int i = 0; i < len; i++)
		for (int j = i + 1; j < len; j++)
			if (cmp->isLess(array[j], array[i]))
				swap(array[i], array[j]);
}
