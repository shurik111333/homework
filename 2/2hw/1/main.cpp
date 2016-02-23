#include <iostream>
#include "ISort.h"
#include "QSort.h"
#include "HeapSort.h"
#include "BubbleSort.h"

using namespace std;

void printSortedArray(ISort *sorter, int *array, int length)
{
	sorter->sort(array, length);
	for (int i = 0; i < length; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
	delete[] array;
}

int *copyArray(int *array, int len)
{
	int *newArray = new int[len];
	for (int i = 0; i < len; i++)
	{
		newArray[i] = array[i];
	}
	return newArray;
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
	cout << "Quick sort: ";
	printSortedArray(new QSort(), copyArray(array, len), len);
	cout << "Heap sort: ";
	printSortedArray(new HeapSort(), copyArray(array, len), len);
	cout << "Bubble sort: ";
	printSortedArray(new BubbleSort(), array, len);
	return 0;
}

