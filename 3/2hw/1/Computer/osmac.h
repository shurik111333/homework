#pragma once

#include "os.h"

class OSMac : public OS
{
public:
	OSMac():
	    OS(10)
	{}

	virtual string getName() const
	{
		return "Mac";
	}

private:
	static const int infectionChance = 10;
};
