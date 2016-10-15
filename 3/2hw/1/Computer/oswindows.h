#pragma once

#include "os.h"

class OSWindows : public OS
{
public:
	OSWindows():
	    OS(40)
	{}

	virtual string getName() const
	{
		return "Windows";
	}

private:
	static const int infectionChance = 40;
};
