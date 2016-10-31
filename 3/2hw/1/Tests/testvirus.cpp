#include "testvirus.h"

bool TestVirus::tryInfect(Computer &computer) const
{
	computer.setInfected(true);
	return true;
}
