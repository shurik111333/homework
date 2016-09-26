#pragma once

#include "os.h"

class OSMac : public OS
{
public:
	OSMac():
	    OS(10)
	{}

private:
	static const int infectionChance = 10;
};
