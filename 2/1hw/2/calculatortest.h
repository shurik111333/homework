#pragma once

#include <QtCore/QObject>
#include <QtTest/QtTest>
#include <Calculator.h>
#include "StackArray.h"

class CalculatorTest : public QObject
{
	Q_OBJECT

public:
	explicit CalculatorTest(QObject *parent = 0):
	    QObject(parent)
	{}

private:
	IStack<double> *result;
	IStack<Calculator::Operator*> *operators;

private slots:
	void init()
	{
		result = new StackArray<double>();
		operators = new StackArray<Calculator::Operator*>();
	}

	void cleanup()
	{
		delete result;
		delete operators;
	}

	void testCalculateNumber()
	{
		QCOMPARE(Calculator::calculate("42", *result, *operators), 42.0);
	}

	void testCalculateAddition()
	{
		QCOMPARE(Calculator::calculate("5 + 12", *result, *operators), 17.0);
	}

	void testCalculateMinus()
	{
		QCOMPARE(Calculator::calculate("5 - 12", *result, *operators), -7.0);
	}

	void testCalculateMultiply()
	{
		QCOMPARE(Calculator::calculate("5 * 12", *result, *operators), 60.0);
	}

	void testCalculateDivision()
	{
		QCOMPARE(Calculator::calculate("5 / 12", *result, *operators), 5.0 / 12);
	}

	void testCalculateFewOperators()
	{
		QCOMPARE(Calculator::calculate("5 + 12 - 3 * 4", *result, *operators), 5.0);
	}

	void testCalculateBrackets()
	{
		QCOMPARE(Calculator::calculate("5 + 12 - (3 + 7) / 2", *result, *operators), 12.0);
	}
};
