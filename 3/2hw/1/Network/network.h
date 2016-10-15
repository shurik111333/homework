#pragma once

#include <vector>
#include <iostream>
#include "../Computer/computer.h"
#include "../Virus/ivirus.h"
#include "inetworkgenerator.h"
#include "networkgeneratorcomplete.h"

using std::vector;
using std::ostream;

/// Network with computers
class Network
{
public:
	Network(const vector<Computer*> &computers, IVirus *virus, INetworkGenerator *netGen = new NetworkGeneratorComplete());
	~Network();

	/// DO a next step of infection
	void nextStep();
	const vector<Computer*> &getComputers() const;
	/// Return number of infected computers
	int getInfectedCount() const;
	/// Print infection computers to out
	void printStatus(ostream &out) const;

private:
	int count = 0;
	int infectedCount = 0;
	IVirus *virus = nullptr;
	INetworkGenerator *networkGenerator = nullptr;
	vector<Computer*> computers;
	vector<vector<bool>> network;
};
