#pragma once

#include <QString>

class IHash
{
public:
	virtual unsigned int getHash(QString &str) const = 0;
};
