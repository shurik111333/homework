#pragma once

#include "IPrint.h"
#include <fstream>

class PrintFile : public IPrint
{
public:
	/**
	 * @brief Open output file stream
	 * @param fileName Name of output file
	 */ 
	PrintFile(char *fileName);
	
	void print(int n);
	
	/**
	 * @brief Close output file stream
	 */
	~PrintFile();
private:
	std::ofstream fout;
};
