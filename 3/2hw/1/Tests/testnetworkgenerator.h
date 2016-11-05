#pragma once

#include <fstream>
#include <string>
#include "Network/inetworkgenerator.h"

class TestNetworkGenerator : public INetworkGenerator
{
public:
	TestNetworkGenerator(std::string name):
	    fileName(name)
	{}

	virtual ~TestNetworkGenerator()
	{}

	virtual vector<vector<bool>> generate(int size) const
	{
		std::ifstream fin(fileName);
		vector<vector<bool>> res(size);
		for (int i = 0; i < size; i++)
		{
			vector<bool> v(size);
			for (int j = 0; j < size; j++)
			{
				int x = 0;
				fin >> x;
				v[j] = x == 1;
			}
			res[i] = v;
		}
		return res;
	}

private:
	std::string fileName;
};
