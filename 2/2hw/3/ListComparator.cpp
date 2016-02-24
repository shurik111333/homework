#include "ListComparator.h"

bool ListComparator::operator <(const ListComparator &structure) const
{
	return this->count() < structure.count();
}

bool ListComparator::operator ==(const ListComparator &structure) const
{
	return this->count() == structure.count();
}