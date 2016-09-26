#pragma once;

#include <vector>
#include "computer.h"
#include "inetworkgenerator.h"

using std::vector;

class Network
{
public:
	Network(int count);

	void nextStep();
	const vector<Computer> &getComputers() const;
	int getInfectedCount() const;

private:
	int count = 0;
	int infectedCount = 0;
	INetworkGenerator *networkGenerator = nullptr;
	vector<Computer> computers;
	vector<vector<bool>> network;
};
