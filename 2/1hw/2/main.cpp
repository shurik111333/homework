#include <iostream>
#include <string>
#include "Calculator.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "��������� ��������� �������������� ��������� � ������ �������." << endl;
	cout << "������� ���������:" << endl;
	string expr;
	getline(cin,expr);
	cout << "���������: " << Calculator::calculate(expr) << endl;
	return 0;
}

