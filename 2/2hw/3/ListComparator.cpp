#include "ListComparator.h"

bool ListComparator::operator <(const ListComparator &structure) const
{
	return this->getCount() < structure.getCount();
}

bool ListComparator::operator ==(const ListComparator &structure) const
{
	return this->getCount() == structure.getCount();
}