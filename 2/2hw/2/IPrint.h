#pragma once

/**
 * @brief Interface for print number with space
 */
class IPrint
{
public:
	void virtual print(int n) = 0;
	
	virtual ~IPrint()
	{}
};