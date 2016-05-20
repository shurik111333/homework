#pragma once

#include "comparator.h"

/// Comparator, that compared int values
class IntComparator : public Comparator<int>
{
public:
	IntComparator()
	{}

	bool isLess(const int &a, const int &b) const
	{
		return a > b;
	}
};
