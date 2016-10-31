#pragma once

#include "Virus/ivirus.h"

//Virus for unit test. Always infect computer
class TestVirus : public IVirus
{
public:
	virtual ~TestVirus()
	{}

	virtual bool tryInfect(Computer &computer) const;
};
