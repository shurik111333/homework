// 11.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>

using namespace std;

void qSort(int left, int right, int arr[])
{
	int leftIndex = left;
	int rightIndex = right;
	int comparingElement = arr[(left + right) / 2];
	while (leftIndex < rightIndex)
	{
		while (arr[leftIndex] < comparingElement)
		{
			leftIndex++;
		}
		while (arr[rightIndex] > comparingElement)
		{
			rightIndex--;
		}
		if (leftIndex <= rightIndex)
		{
			swap(arr[leftIndex], arr[rightIndex]);
			leftIndex++;
			rightIndex--;
		}
	}
	if (leftIndex < right)
	{
		qSort(leftIndex, right, arr);
	}
	if (rightIndex > left)
	{
		qSort(left, rightIndex, arr);
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "Программа сортирует массив по убыванию алгоритмом быстрой сортировки" << endl;
	cout << "Введите количество элементов массива" << endl;
	int n = 0;
	cin >> n;
	cout << "Введите элементы массива" << endl;
	int *inputArray = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> inputArray[i];
	}
	qSort(0, n - 1, inputArray);
	for (int i = 0; i < n; i++)
	{
		cout << inputArray[i] << " ";
	}
	cout << endl;
	delete[] inputArray;
	return 0;
}