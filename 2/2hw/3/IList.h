#pragma once

#include "ListComparator.h"


template <typename T>
/**
 * @brief ADT List.
 */
class IList : public ListComparator
{
public: 
	void virtual insert(T value, int index) = 0;
	
	/**
	 * @brief Remove the first occurrence of value.
	 * @param value
	 * @return Return true - if element was removed, false - if element was not found.
	 */
	bool virtual remove(T value) = 0;
	
	/**
	 * @brief Find first occurrence of value.
	 * @param value
	 * @return Return index of first occurrence or -1, if element was not found.
	 */
	int virtual findElementId(T value) const = 0;
	
	T virtual operator [](const int index) const = 0;
	
	virtual ~IList()
	{}
};