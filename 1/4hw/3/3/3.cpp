// 3.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>

using namespace std;

const int numberOfDigits = 10;

int getLastDigit(int number)
{
	return number % 10;
}

void deleteLastDigit(int &number)
{
	number /= 10;
}

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "Программа переставляет цифры введенного числа так, что бы получилось наименьшее число" << endl;
	int number = 0;
	cin >> number;
	int countDigits[numberOfDigits] = {};
	while (number > 0)
	{
		countDigits[getLastDigit(number)]++;
		deleteLastDigit(number);
	}
	for (int currentDigit = 0; currentDigit < numberOfDigits; currentDigit++)
	{
		for (int countDigit = 0; countDigit < countDigits[currentDigit]; countDigit++)
		{
			cout << currentDigit;
		}
	}
	cout << endl;
	return 0;
}

