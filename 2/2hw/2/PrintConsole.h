#pragma once

#include "IPrint.h"

class PrintConsole : public IPrint
{
public:
	PrintConsole();
	
	void print(int n);
	
	~PrintConsole();
};
