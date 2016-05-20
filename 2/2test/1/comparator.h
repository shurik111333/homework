#pragma once

/// Represents interface that compare two objects
template <typename T>
class Comparator
{
public:
	virtual ~Comparator()
	{}

	/// @return Returns true, if the first object is lesser than second
	virtual bool isLess(const T &obj1, const T &obj2) const = 0;
};
