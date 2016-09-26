#pragma once

#include "inetworkgenerator.h"

///Realizes generator which generate complet graph
class NetworkGeneratorComplete : public INetworkGenerator
{
public:
	NetworkGeneratorComplete();

	vector<vector<bool>> generate(int size) const;
};
