#pragma once

#include <QString>
#include "ihash.h"

class LinearHash : public IHash
{
public:
	LinearHash();
	~LinearHash();

	unsigned int getHash(const QString &str) const;

private:
	const int defaultModule = 1e9 + 7;
	int module;
};
