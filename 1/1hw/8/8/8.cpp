// 8.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>

using namespace std;

long factorialRecursive(int n)
{
	if (n == 0)
		return 1;
	else
		return n * factorialRecursive(n - 1);
}

long factorialIterate(int n)
{
	int result = 1;
	for (int i = 2; i <= n; i++)
	{
		result *= i;
	}
	return result;
}

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "Программа считает факториал числа n" << endl;
	cout << "Введите число n" << endl;
	int n = 0;
	cin >> n;
	cout << "Рекурсивный подсчет: " << factorialRecursive(n) << endl;
	cout << "Итеративный подсчет: " << factorialIterate(n) << endl;
	return 0;
}

