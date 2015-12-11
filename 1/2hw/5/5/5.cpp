// 5.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>

using namespace std;

int rightSon(int vertex)
{
	return vertex * 2 + 1;
}

int leftSon(int vertex)
{
	return vertex * 2;
}

void heapify(int vertex, int heap[], int size)
{
	while (vertex > 0)
	{
		int maxVertex = vertex;
		if (leftSon(vertex) <= size && heap[leftSon(vertex) - 1] > heap[maxVertex - 1])
		{
			maxVertex = leftSon(vertex);
		}
		if (rightSon(vertex) <= size && heap[rightSon(vertex) - 1] > heap[maxVertex - 1])
		{
			maxVertex = rightSon(vertex);
		}
		if (maxVertex != vertex)
		{
			swap(heap[maxVertex - 1], heap[vertex - 1]);
			vertex = maxVertex;
		}
		else
		{
			vertex /= 2;
		}
	}
}

void buildHeap(int size, int heap[])
{
	for (int i = size; i > 0; i--)
	{
		heapify(i, heap, size);
	}
}

void heapSort(int size, int inputArray[])
{
	buildHeap(size, inputArray);
	for (int i = size; i > 0; i--)
	{
		swap(inputArray[0], inputArray[size - 1]);
		size--;
		heapify(1, inputArray, size);
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "Программа сортирует массив по возрастанию алгоритмом пирамидальной сортировки" << endl;
	cout << "Введите количество элементов в массиве" << endl;
	int size = 0;
	cin >> size;
	cout << "Введите элементы массива" << endl;
	int *inputArray = new int[size];
	for (int i = 0; i < size; i++)
	{
		cin >> inputArray[i];
	}
	heapSort(size, inputArray);
	for (int i = 0; i < size; i++)
	{
		cout << inputArray[i] << " ";
	}
	cout << endl;
	return 0;
}