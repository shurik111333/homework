#pragma once

/**
 * @brief Interface of the comparater, which compare the number of elements in list.
 */
class ListComparator
{
public:
	/**
	 * @brief Count number of elements in list.
	 * @return Return number of elements in list.
	 */
	int virtual getCount() const = 0;
	
	bool virtual operator <(const ListComparator &structure) const;
	
	bool virtual operator ==(const ListComparator &structure) const;
	
	virtual ~ListComparator()
	{}
};