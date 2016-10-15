#pragma once

#include <string>

using std::string;

/// Interface for computer os
class OS
{
public:
	virtual ~OS()
	{}
	/**
	 * @brief getInfectionChance
	 * @return Chance of virus infection in range [0..100]
	 */
	virtual int getInfectionChance() const
	{
		return chance;
	}

	/**
	 * @brief getName
	 * @return Name of the current OS
	 */
	virtual string getName() const = 0;

protected:
	OS(int chance):
	    chance(chance)
	{}

private:
	int chance = 0;
};
