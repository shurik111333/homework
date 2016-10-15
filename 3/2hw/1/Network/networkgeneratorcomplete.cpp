#include "networkgeneratorcomplete.h"

NetworkGeneratorComplete::NetworkGeneratorComplete()
{

}

vector<vector<bool>> NetworkGeneratorComplete::generate(int size) const
{
	vector<vector<bool>> res;
	for (int i = 0; i < size; i++)
	{
		vector<bool> v;
		for (int j = 0; j < size; j++)
			v.push_back(i != j);
		res.push_back(v);
	}
	return res;
}
