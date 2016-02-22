#include "PrintFile.h"
#include <fstream>

PrintFile::PrintFile(char *fileName)
{
	fout.open(fileName);
}

void PrintFile::print(int n)
{
	fout << n << " ";
}

PrintFile::~PrintFile()
{
	fout.close();
}