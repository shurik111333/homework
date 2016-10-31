#include <cstdlib>
#include <ctime>
#include "network.h"
#include "networkgeneratorcomplete.h"
#include "Computer/oswindows.h"
#include "Computer/osmac.h"
#include "Computer/oslinux.h"

Network::Network(const vector<Computer*> &computers, IVirus *virus, INetworkGenerator *netGen):
    count(computers.size()),
    virus(virus),
    networkGenerator(netGen)
{
	this->computers = computers;
	network = networkGenerator->generate(count);
	infectedCount = 0;
	for (auto c : computers)
		if (c->isInfected())
			infectedCount++;
}

Network::~Network()
{
	delete networkGenerator;
	delete virus;
	for (auto c : computers)
		delete c;
}

void Network::nextStep()
{
	auto comps = getInfectedComputers();
	for (auto c : comps)
	{
		for (int j = 0; j < count; j++)
		{
			if (!network[c->getId()][j] || computers[j]->isInfected())
				continue;
			if (virus->tryInfect(*computers[j]))
			{
				infectedCount++;
			}
		}
	}
}

const vector<Computer*> Network::getInfectedComputers() const
{
	vector<Computer *> res;
	for (auto c : computers)
		if (c->isInfected())
			res.push_back(c);
	return res;
}

int Network::getInfectedCount() const
{
	return infectedCount;
}

void Network::printStatus(ostream &out) const
{
	out << "Infected:";
	for (auto c : computers)
	{
		if (c->isInfected())
			out << " " << c->getId() + 1 << "(" << c->getOs()->getName() << ")";
	}
	out << "\n";
}
