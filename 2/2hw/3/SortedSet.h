#pragma once

#include "ListComparator.h"

class SortedSet
{
public:
	/**
	 * @brief Create
	 * @param size Initial number of elements.
	 */
	SortedSet(int size = minSize);
	
	bool add(ListComparator *input);
	
	/**
	 * @brief Remove object of ListComparator, that equal input.
	 * @param input
	 * @return Return true, if element was deleted, false, if element was no found
	 */
	bool remove(ListComparator *input);
	
	bool contains(ListComparator *input) const;
	
	ListComparator *min() const;
	
	ListComparator *max() const;
	/**
	 * @brief Remove all objects of ListComparator from Set.
	 */
	void clear();
	
	bool empty() const;
	
	~SortedSet();
	
private:
	int count;
	int size;
	static const int minSize = 5;
	ListComparator **array;
	
	void increaseArray();
	
	/**
	 * @brief Find place for insert input.
	 * @param input
	 * @return Return index of this place.
	 */
	int find(ListComparator *input) const;
};
