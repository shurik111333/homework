#pragma once

#include "inetworkgenerator.h"

///Realizes generator which generate complete graph
class NetworkGeneratorComplete : public INetworkGenerator
{
public:
	NetworkGeneratorComplete();
	virtual ~NetworkGeneratorComplete()
	{}

	vector<vector<bool>> generate(int size) const;
};
