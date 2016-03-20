#pragma once

#include <QString>

class IHash
{
public:
	virtual ~IHash()
	{}

	virtual unsigned int getHash(const QString &str) const = 0;
};
