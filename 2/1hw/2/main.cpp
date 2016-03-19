#include <iostream>
#include <string>
#include "Calculator.h"
#include "IStack.h"
#include "StackArray.h"
#include "StackPointer.h"
#include "stackarraytest.h"
#include "stackpointertest.h"

using namespace std;

int main()
{
	StackArrayTest testArray;
	QTest::qExec(&testArray);
	StackPointerTest testPointer;
	QTest::qExec(&testPointer);

	cout << "This programm calculate arithmetic exressions with integer numbers." << endl;
	cout << "Enter expression:" << endl;
	string expr;
	getline(cin, expr);
	IStack<double> *result = new StackArray<double>();
	IStack<Calculator::Operator*> *operators = new StackArray<Calculator::Operator*>();
	cout << "Result (use StackArray): " << Calculator::calculate(expr, *result, *operators) << endl;
	delete result;
	delete operators;
	result = new StackPointer<double>();
	operators = new StackPointer<Calculator::Operator*>();
	cout << "Result (use StackPointer): " << Calculator::calculate(expr, *result, *operators) << endl;
	delete result;
	delete operators;
	return 0;
}

