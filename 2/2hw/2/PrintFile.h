#pragma once

#include "IPrint.h"
#include <fstream>

class PrintFile : public IPrint
{
public:
	PrintFile(char *fileName);
	
	void print(int n);
	
	~PrintFile();
private:
	std::ofstream fout;
};
