#include "computer.h"

Computer::Computer(OS *os, int id):
    os(os),
    id(id)
{}

const OS *Computer::getOs() const
{
	return os;
}

int Computer::getInfectionChance() const
{
	return os->getInfectionChance();
}

void Computer::setInfected(bool isInfected)
{
	infected = isInfected;
}

bool Computer::isInfected() const
{
	return infected;
}

int Computer::getId()
{
	return id;
}
