// 2.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>

using namespace std;

long power(int a, int n)
{
	if (n == 0)
		return 1;
	if (n % 2 == 1)
		return a * power(a, n - 1);
	else
	{
		int temp = power(a, n / 2);
		return temp * temp;
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "Программа возводит число a в степень n\n";
	cout << "Введите числа a и n через пробел\n";
	int a = 0, n = 0;
	cin >> a >> n;
	long result = power(a, abs(n));
	cout << "Ответ: ";
	if (n < 0)
	{
		cout << 1.0 / result << "\n";
	}
	else
	{
		cout << result << "\n";
	}
	return 0;
}