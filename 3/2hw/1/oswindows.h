#pragma once

#include "os.h"

class OSWindows : public OS
{
public:
	OSWindows():
	    OS(40)
	{}

private:
	static const int infectionChance = 40;
};
