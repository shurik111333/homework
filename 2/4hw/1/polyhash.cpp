#include "polyhash.h"

PolyHash::PolyHash()
    :module(defaultModule), multiplier(defaultMultiplier)
{}

unsigned int PolyHash::getHash(QString &str) const
{
	unsigned long long result = 0;
	for (int i = 0; i < str.length(); i++)
	{
		result = (result * multiplier + (unsigned char)(str[i].toLatin1())) % module;
	}
	return result;
}
