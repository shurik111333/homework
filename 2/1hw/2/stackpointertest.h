#pragma once

#include <QtCore/QObject>
#include <QtTest/QtTest>
#include "IStack.h"
#include "StackPointer.h"

class StackPointerTest : public QObject
{
	Q_OBJECT

public:
	explicit StackPointerTest(QObject *parent = 0):
	    QObject(parent)
	{}

private:
	IStack<int> *stack;

private slots:
	void init()
	{
		stack = new StackPointer<int>();
	}

	void cleanup()
	{
		delete stack;
	}

	void testEmptyStack()
	{
		QVERIFY(stack->isEmpty());
	}

	void testNonEmptyStack()
	{
		stack->push(42);
		QVERIFY(!stack->isEmpty());
	}

	void testAddElement()
	{
		stack->push(42);
		QCOMPARE(stack->getTop(), 42);
	}

	void testPopElement()
	{
		stack->push(20);
		QCOMPARE(stack->pop(), 20);
		QVERIFY(stack->isEmpty());
	}

	void testPushElements()
	{
		for (int i = 0; i < 5; i++)
		{
			stack->push(i);
		}
		for (int i = 4; i >= 0; i--)
		{
			QCOMPARE(stack->pop(), i);
		}
	}

	void testEmptyStackAfterPops()
	{
		for (int i = 0; i < 5; i++)
		{
			stack->push(i);
		}
		for (int i = 0; i < 5; i++)
		{
			stack->pop();
		}
		QVERIFY(stack->isEmpty());
	}
};
