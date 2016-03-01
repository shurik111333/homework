#include <iostream>
#include "ISort.h"
#include "QSort.h"
#include "HeapSort.h"
#include "BubbleSort.h"

using namespace std;

/**
 * @brief Sort input array with sorter, print it in console and delete.
 * @param sorter Object of sorter class with ISort interface
 * @param array
 * @param length
 */
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

/**
 * @brief Copy input array
 * @param array
 * @param len
 * @return Return pointer to copyied array
 */
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
	cout << "Enter size of array:" << endl;
	int len = 0;
	cin >> len;
	cout << "Enter array:" << endl;
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

