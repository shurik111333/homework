// 2.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "Программа для нахождения неполного частного от деления a на b" << endl << "Введите a и b" << endl;
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
	cout << "Ответ: " << quotient << endl;
	return 0;
}

