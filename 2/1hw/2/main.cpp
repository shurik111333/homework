#include <iostream>
#include <string>
#include "Calculator.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "Программа вычисляет арифметические выражения с целыми числами." << endl;
	cout << "Введите выражение:" << endl;
	string expr;
	getline(cin,expr);
	cout << "Результат: " << Calculator::calculate(expr) << endl;
	return 0;
}

