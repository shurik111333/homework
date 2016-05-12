#pragma once

template <typename T>
class IList
{
public:
	void virtual insert(T value, int index) = 0;
	void virtual remove(T value) = 0;
	int virtual findElementId(T value) const = 0;
	int virtual length() const = 0;
	T virtual operator [](const int index) const = 0;
	virtual ~IList()
	{}
};
