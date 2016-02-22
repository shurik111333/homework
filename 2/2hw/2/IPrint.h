#pragma once

class IPrint
{
public:
	void virtual print(int n) = 0;
	
	virtual ~IPrint()
	{}
};