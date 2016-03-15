#include "linearhash.h"

LinearHash::LinearHash():
    module(defaultModule)
{}

LinearHash::~LinearHash()
{}

unsigned int LinearHash::getHash(const QString &str) const
{
	long long result = 0;
	for (int i = 0; i < str.length(); i++)
	{
		result = (result + (unsigned char)(str[i].toLatin1()) * i) % module;
	}
	return result;
}
