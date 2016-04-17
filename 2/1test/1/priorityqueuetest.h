#pragma once

#include <QtCore/QObject>
#include <QtTest/QtTest>
#include <cstdlib>
#include <ctime>
#include "priorityqueue.h"

class PriorityQueueTest : public QObject
{
	Q_OBJECT

public:
	explicit PriorityQueueTest(QObject *parent = 0):
	    QObject(parent)
	{}

private:
	PriorityQueue<int> queue;

private slots:
	void init()
	{
		queue.clear();
	}

	void testEmptyQueue()
	{
		QVERIFY(queue.empty());
	}

	void testDequeueFromEmptyQueue()
	{
		QVERIFY_EXCEPTION_THROWN(queue.dequeue(), EmptyQueue);
	}

	void testInsertAndCheckOneElement()
	{
		queue.enqueue(1, 1);
		QCOMPARE(queue.dequeue(), 1);
	}

	void testClearQueue()
	{
		for (int i = 0; i < 10; i++)
		{
			queue.enqueue(i, i);
		}
		queue.clear();
		QVERIFY(queue.empty());
	}

	void randomTests()
	{
		srand(time(0));
		for (int i = 0; i < 1000; i++)
		{
			int n = rand() % 1000 + 1;
			for (int j = 0; j < n; j++)
			{
				int value = rand() % 1000 + 1;
				queue.enqueue(value, value);
			}
			int lastValue = queue.dequeue();
			for (int j = 1; j < n; j++)
			{
				int newValue = queue.dequeue();
				QVERIFY(lastValue >= newValue);
				lastValue = newValue;
			}
			QVERIFY(queue.empty());
		}
	}
};
