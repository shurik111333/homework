// 1.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include <iostream>
#include <limits.h>
#include <cstring>

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "��������� ���� ������������ �������, ������� ����������� ����� 1 ����" << endl;
	cout << "������� ���������� ���������" << endl;
	int number = 0;
	cin >> number;
	cout << "������� �������� ����� ������" << endl;
	int *inputArray = new int[number];
	int minElement = INT_MAX;
	int maxElement = INT_MIN;
	memset(inputArray, 0, number * sizeof(inputArray[0]));
	for (int i = 0; i < number; i++)
	{
		cin >> inputArray[i];
		if (inputArray[i] > maxElement)
		{
			maxElement = inputArray[i];
		}
		if (inputArray[i] < minElement)
		{
			minElement = inputArray[i];
		}
	}
	int *countElements = new int[maxElement - minElement + 1];
	memset(countElements, 0, (maxElement - minElement + 1) * sizeof(countElements[0]));
	for (int i = 0; i < number; i++)
	{
		countElements[inputArray[i] - minElement]++;
	}
	delete[] inputArray;
	int answer = INT_MIN;
	for (int i = maxElement - minElement; i >= 0; i--)
	{
		if (countElements[i] > 1)
		{
			answer = i + minElement;
			break;
		}
	}
	delete[] countElements;
	if (answer == INT_MIN)
	{
		cout << "�� ������ �������, ��������������� ��������" << endl;
	}
	else
	{
		cout << "�����: " << answer << endl;
	}
	return 0;
}