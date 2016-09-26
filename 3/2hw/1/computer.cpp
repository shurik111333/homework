#include "computer.h"

Computer::Computer(OS *os):
    os(os)
{}

double Computer::getInfectionChance() const
{
	return os->getInfectionChance();
}

void Computer::setInfected(double isInfected)
{
	infected = isInfected;
}

bool Computer::isInfected()
{
	return infected;
}
