#include <iostream>
#include <string>
#include "Calculator.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "This programm calculate arithmetic exressions with integer numbers." << endl;
	cout << "Enter expression:" << endl;
	string expr;
	getline(cin,expr);
	cout << "Result: " << Calculator::calculate(expr) << endl;
	return 0;
}

