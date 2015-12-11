// 1.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "Программа считает значение выражения \"x^4 + x^3 + x^2 + x + 1\"\n";
	cout << "Введите число x\n";
	int x = 0;
	cin >> x;
	int x2 = x * x;
	int result = (x2 + 1) * (x2 + x) + 1;
	cout << "Ответ: " << result << endl;
	return 0;
}