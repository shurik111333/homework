#pragma once

#include <QString>
#include "ihash.h"

class PolyHash : public IHash
{
public:
	PolyHash();
	~PolyHash();

	unsigned int getHash(const QString &str) const;

private:
	const int defaultModule = 1e9 + 7;
	const int defaultMultiplier = 53;
	int module;
	int multiplier;
};
