#include <iostream>
#include <fstream>
#include <limits.h>

using namespace std;

const int maxLen = 256;

int min(int a, int b)
{
	return a < b ? a : b;
}

int max(int a, int b)
{
	return a > b ? a : b;
}

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "Введите имя файла с двумерным массивом" << endl;
	char fileName[maxLen] = {};
	cin >> fileName;
	ifstream fin(fileName);
	int n = 0;
	int m = 0;
	fin >> n >> m;
	int **array = new int*[n];
	int *minRow = new int[n];
	int *maxColumn = new int[m];
	for (int i = 0; i < n; i++)
	{
		minRow[i] = INT_MAX;
	}
	for (int i = 0; i < m; i++)
	{
		maxColumn[i] = INT_MIN;
	}
	for (int i = 0; i < n; i++)
	{
		array[i] = new int[m];
		for (int j = 0; j < m; j++)
		{
			fin >> array[i][j];
			minRow[i] = min(minRow[i], array[i][j]);
			maxColumn[j] = max(maxColumn[j], array[i][j]);
		}
	}
	fin.close();
	for (int i = 0; i < n; i++)
	{
		delete[] array[i];
	}
	delete[] array;
	cout << "Седловые точки:" << endl;
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (minRow[i] == maxColumn[j])
			{
				cout << minRow[i] << " (" << i << "; " << j << ")" << endl;
				count++;
			}
		}
	}
	if (count == 0)
	{
		cout << "отсутствуют" << endl;
	}
	delete[] minRow;
	delete[] maxColumn;
	return 0;
}

