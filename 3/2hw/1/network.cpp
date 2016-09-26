#include <cstdlib>
#include <ctime>
#include "network.h"
#include "oswindows.h"
#include "osmac.h"
#include "oslinux.h"
#include "networkgeneratorcomplete.h"

Network::Network(int count):
    count(count),
    networkGenerator(new NetworkGeneratorComplete())
{
	srand(time(0));
	computers.resize(count);
	network = networkGenerator->generate(count);
	for (int i = 0; i < count; i++)
	{
		int x = rand() % 3;
		OS *os = nullptr;
		switch (x)
		{
			case 0:
				os = new OSWindows();
				break;
			case 1:
				os = new OSLinux();
				break;
			case 2:
				os = new OSMac();
				break;
		}
		computers[i] = Computer(os);
	}
	computers[rand() % count].setInfected(true);
	infectedCount = 1;
}

void Network::nextStep()
{
	for (int i = 0; i < count; i++)
	{
		if (!computers[i].isInfected())
			continue;

		for (int j = 0; j < count; j++)
		{
			if (!network[i][j] || computers[j].isInfected())
				continue;
			int chance = (rand() % 101);
			int compChance = computers[j].getInfectionChance();
			if (chance <= compChance)
			{
				computers[j].setInfected(true);
				infectedCount++;
			}
		}
	}
}

const vector<Computer> &Network::getComputers() const
{
	return computers;
}

int Network::getInfectedCount() const
{
	return infectedCount;
}
