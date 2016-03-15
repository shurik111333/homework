#pragma once

#include <QString>

class IHash
{
public:
	virtual unsigned int getHash(const QString &str) const = 0;

	virtual ~IHash()
	{}
};
