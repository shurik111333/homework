#pragma once

#include "os.h"

class OSLinux : public OS
{
public:
	OSLinux():
	    OS(20)
	{}

private:
	static const int infectionChance = 20;
};
