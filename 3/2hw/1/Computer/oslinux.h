#pragma once

#include "os.h"

class OSLinux : public OS
{
public:
	OSLinux():
	    OS(20)
	{}

	virtual string getName() const
	{
		return "Linux";
	}

private:
	static const int infectionChance = 20;
};
