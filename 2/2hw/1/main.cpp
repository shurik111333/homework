#include <iostream>
#include "ISort.h"
#include "QSort.h"
using namespace std;

void printSortedArray(ISort *sorter, int *array, int length)
{
	sorter->sort(array, 0, length - 1);
	for (int i = 0; i < length; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "¬ведите количество элементов в массиве" << endl;
	int len = 0;
	cin >> len;
	cout << "¬ведите массив" << endl;
	int *array = new int[len];
	for (int i = 0; i < len; i++)
	{
		cin >> array[i];
	}
	printSortedArray(new QSort(), array, len);
	return 0;
}

