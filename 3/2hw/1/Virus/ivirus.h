#pragma once

#include "../Computer/computer.h"

/// Interface for algorithm for infect computer
class IVirus
{
public:
	virtual ~IVirus()
	{}

	virtual bool tryInfect(Computer &computer) const = 0;
};
