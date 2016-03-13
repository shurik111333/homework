#pragma once

#include "ihash.h"

class PolyHash : public IHash
{
public:
	PolyHash();
	
	unsigned int getHash(QString &str) const;
	
private:
	const int defaultModule = 1e9 + 7;
	const int defaultMultiplier = 53;
	int module;
	int multiplier;
};
