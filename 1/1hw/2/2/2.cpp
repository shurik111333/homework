// 2.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "��������� ��� ���������� ��������� �������� �� ������� a �� b" << endl << "������� a � b" << endl;
	int a = 0;
	int b = 0;
	cin >> a >> b;
	int newA = abs(a);
	int newB = abs(b);
	int quotient = 0;
	int number = 0;
	while (number <= newA)
	{
		number += newB;
		quotient++;
	}
	if (a >= 0 || newA == newB * (quotient - 1))
	{
		quotient--;
	}
	if (a * b < 0)
	{
		quotient = -quotient;
	}
	cout << "�����: " << quotient << endl;
	return 0;
}

