#include <iostream>
#include <cmath>
#include <QtTest/QtTest>
#include "IPrint.h"
#include "PrintConsole.h"
#include "PrintFile.h"
#include "PrintMatrix.h"
#include "PrintMatrixTest.h"

using namespace std;

const int maxLen = 256;

IPrint *getPrintMethod()
{
	int type = 0;
	while (type != 1 && type != 2)
	{
		cout << "Select output method:" << endl;
		cout << "1 - console" << endl;
		cout << "2 - file" << endl;
		cin >> type;
	}
	if (type == 1)
		return new PrintConsole();
	cout << "Enter file name:" << endl;
	char fileName[maxLen] = {};
	cin >> fileName;
	return new PrintFile(fileName);
}

int main()
{
	PrintMatrixTest test;
	QTest::qExec(&test);

	setlocale(LC_ALL, "rus");
	cout << "This porgramm print array NxN in spiral order." << endl;
	cout << "Enter odd number N - size of array:" << endl;
	int n = 0;
	cin >> n;
	cout << "Enter array:" << endl;
	int **inputArray = new int*[n];
	for (int i = 0; i < n; i++)
	{
		inputArray[i] = new int[n];
		for (int j = 0; j < n; j++)
		{
			cin >> inputArray[i][j];
		}
	}
	IPrint *printer = getPrintMethod();
	PrintMatrix::print(inputArray, n, printer);
	delete printer;
	for (int i = 0; i < n; i++)
	{
		delete[] inputArray[i];
	}
	delete[] inputArray;
	cout << endl;
	return 0;
}
