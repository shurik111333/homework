#pragma once

class OS
{
public:
	virtual int getInfectionChance() const
	{
		return chance;
	}

protected:
	OS(int chance):
	    chance(chance)
	{}

private:
	int chance = 0;
};
