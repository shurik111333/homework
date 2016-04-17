#pragma once

#include <QtCore/QObject>
#include <QtTest/QtTest>
#include <cmath>
#include "Calculator.h"

class CalculatorTest : public QObject
{
	Q_OBJECT

public:
	explicit CalculatorTest(QObject *parent = 0):
	    QObject(parent)
	{}

private:
	const double eps = 1e-10;

private slots:
	void testCalculateNumber()
	{
		QCOMPARE(Calculator::calculate("42"), 42.0);
	}

	void testCalculateAddition()
	{
		QCOMPARE(Calculator::calculate("5 + 12"), 17.0);
	}

	void testCalculateMinus()
	{
		QCOMPARE(Calculator::calculate("5 - 12"), -7.0);
	}

	void testCalculateMultiply()
	{
		QCOMPARE(Calculator::calculate("5 * 12"), 60.0);
	}

	void testCalculateDivision()
	{
		QCOMPARE(Calculator::calculate("5 / 12"), 5.0 / 12);
	}

	void testDivisionByZero()
	{
		QVERIFY_EXCEPTION_THROWN(Calculator::calculate("5 / (2 - 2)"), QString);
	}

	void testCalculateFewOperators()
	{
		QCOMPARE(Calculator::calculate("5 + 12 - 3 * 4"), 5.0);
	}

	void testCalculateBrackets()
	{
		QCOMPARE(Calculator::calculate("5 + 12 - (3 + 7) / 2"), 12.0);
	}

	void testCalculateSqrt()
	{
		QCOMPARE(Calculator::calculate("sqrt 2"), sqrt(2));
	}

	void testCalculateSqrtOfExpression()
	{
		QCOMPARE(Calculator::calculate("sqrt (2 * 3 + 1)"), sqrt(7));
	}

	void testCalculateSqrtFormNegativeNumber()
	{
		QVERIFY_EXCEPTION_THROWN(Calculator::calculate("5 + sqrt (6 / 3 - 5)"), QString);
	}
};
