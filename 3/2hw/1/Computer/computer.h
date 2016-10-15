#pragma once

#include "os.h"

class Computer
{
public:
	Computer()
	{}

	Computer(OS *os, int id);

	const OS *getOs() const;
	int getInfectionChance() const;
	void setInfected(bool isInfected);
	bool isInfected() const;
	int getId();

private:
	OS *os = nullptr;
	bool infected = false;
	int id;
};

