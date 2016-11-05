#include "randomvirus.h"
#include <cstdlib>

bool RandomVirus::tryInfect(Computer &computer) const
{
	if (rand() % 100 < computer.getInfectionChance())
	{
		computer.setInfected(true);
		return true;
	}
	return false;
}
