#include <iostream>
#include "tree.h"

using namespace std;

const int maxLen = 256;

FILE *getFileToRead()
{
	char fileName[maxLen] = {};
	cout << "Enter a file name" << endl;
	fgets(fileName, maxLen - 1, stdin);
	deleteNewLineSymbol(fileName);
	FILE *fileToRead = fopen(fileName, "r");
	while (fileToRead == nullptr)
	{
		cout << "Cannot open file. Try again" << endl;
		fgets(fileName, maxLen - 1, stdin);
		deleteNewLineSymbol(fileName);
		fileToRead = fopen(fileName, "r");
	}
	return fileToRead;
}

int main()
{
	FILE *input = getFileToRead();
	Tree tree(input);
	tree.print(cout);
	cout << endl;
	cout << tree.calc();
	return 0;
}
