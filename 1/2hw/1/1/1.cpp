// 1.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include <iostream>

using namespace std;

int fibonachiRecursive(int n)
{
	if (n < 1)
	{
		return 0;
	}
	if (n == 1 || n == 2)
	{
		return 1;
	}
	return fibonachiRecursive(n - 1) + fibonachiRecursive(n - 2);
}

int fibonachiIterative(int n)
{
	if (n < 1)
	{
		return 0;
	}
	int lastNumber = 1;
	int prevNumber = 0;
	int indexLastNumber = 1;
	while (indexLastNumber < n)
	{
		lastNumber = lastNumber + prevNumber;
		prevNumber = lastNumber - prevNumber;
		indexLastNumber++;
	}
	return lastNumber;
}

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "��������� ������� n-�� ����� ���������" << endl;
	cout << "������� n" << endl;
	int n = 0;
	cin >> n;
	cout << "����������� ��������: " << fibonachiIterative(n) << endl;
	cout << "����������� ��������: " << fibonachiRecursive(n) << endl;
	return 0;
}