#pragma once

#include <QtCore/QObject>
#include <QtTest/QtTest>
#include <string>
#include "tree.h"

using namespace std;

class TestTree : public QObject
{
	Q_OBJECT

public:
	explicit TestTree(QObject *parent = 0):
	    QObject(parent)
	{}

private:
	string input;

	void check(int res, const string &strRes)
	{
		Tree t(input);
		QCOMPARE(t.calc(), res);
		QCOMPARE(t.toStdString(), strRes);
	}

private slots:
	void testOneNumber()
	{
		input = "53";
		check(53, "53");
	}

	void testOperationAdd()
	{
		input = "(+ 1 15)";
		check(16, "(1 + 15)");
	}

	void testOperationSubtract()
	{
		input = "(- 1 15)";
		check(-14, "(1 - 15)");
	}

	void testOperationMultiply()
	{
		input = "(* 3 15)";
		check(45, "(3 * 15)");
	}

	void testOperationDivide()
	{
		input = "(/ 30 15)";
		check(2, "(30 / 15)");
	}

	void testDivideByZero()
	{
		input = "(/ 2 (- 3 3))";
		QVERIFY_EXCEPTION_THROWN(check(0, ""), overflow_error);
	}

	void testComplexExressions()
	{
		string inputs[] = {"(+ (* (+ 2 1) (- 3 5)) (/ 10 (+ -5 3)))",
		                   "(/ (+ 22 6) (+ (* 2 2) (/ 3 1)))"};
		int results[] = {-11, 4};
		string strResults[] = {"(((2 + 1) * (3 - 5)) + (10 / (-5 + 3)))",
		                       "((22 + 6) / ((2 * 2) + (3 / 1)))"};
		int len = sizeof(inputs) / sizeof(inputs[0]);
		for (int i = 0; i < len; i++)
		{
			input = inputs[i];
			check(results[i], strResults[i]);
		}
	}
};
