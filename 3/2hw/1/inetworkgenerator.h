#pragma once

#include <vector>

using std::vector;

/// Interface for connected graph generator
class INetworkGenerator
{
public:
	/**
	 * @brief generate Generates adjacency matrix
	 * @param size Number of vertex
	 * @return Adjacency matrix
	 */
	virtual vector<vector<bool>> generate(int size) const = 0;
};
