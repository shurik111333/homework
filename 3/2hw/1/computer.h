#pragma once

#include "os.h"

class Computer
{
public:
	Computer()
	{}

	Computer(OS *os);

	double getInfectionChance() const;
	void setInfected(double isInfected);
	bool isInfected();

private:
	OS *os = nullptr;
	bool infected = false;
};

