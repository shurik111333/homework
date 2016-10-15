#pragma once

#include "ivirus.h"

/// Virus, that try infect randomly. Chance of infection depends of os
class RandomVirus : public IVirus
{
public:
	virtual ~RandomVirus()
	{}

	virtual bool tryInfect(Computer &computer) const;
};
