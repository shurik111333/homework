#pragma once

#include <QtCore/QObject>
#include <QtTest/QtTest>
#include <cstdlib>
#include <ctime>
#include "bubbleSorter.h"
#include "intComparator.h"

class BubbleSorterTest : public QObject
{
	Q_OBJECT

public:
	explicit BubbleSorterTest(QObject *parent = 0):
	    QObject(parent)
	{
		cmp = new IntComparator();
		sorter = new BubbleSorter<int>();
	}

	~BubbleSorterTest()
	{
		delete cmp;
		delete sorter;
	}

private:
	BubbleSorter<int> *sorter;
	Comparator<int> *cmp;
	QList<int> array;
	const int countRandTest = 100;
	const int maxSize = 500;
	const int elementsRange = 1e5;

	void checkSortedArray()
	{
		int length = array.size();
		for (int i = 0; i < length - 1; i++)
		{
			// This condition consider equal elements in the list
			QVERIFY(!cmp->isLess(array[i + 1], array[i]));
		}
	}

private slots:
	void cleanup()
	{
		array.clear();
	}

	void testOneElement()
	{
		array.push_back(10);
		sorter->sort(array, cmp);
		QCOMPARE(array.size(), 1);
		QCOMPARE(array[0], 10);
	}

	void testSortedArray()
	{
		for (int i = 0; i < 10; i++)
		{
			array.push_back(i * 2);
		}
		sorter->sort(array, cmp);
		QCOMPARE(array.size(), 10);
		checkSortedArray();
	}

	void testDecreasingArray()
	{
		for (int i = 0; i < 10; i++)
		{
			array.push_back((9 - i) * 2);
		}
		sorter->sort(array, cmp);
		QCOMPARE(array.size(), 10);
		checkSortedArray();
	}

	void randomTests()
	{
		srand(time(0));
		for (int i = 0; i < maxSize; i++)
			array.push_back(0);  // reserve maxSize elements
		for (int i = 0; i < countRandTest; i++)
		{
			for (int j = 0; j < maxSize; j++)
			{
				array[j] = rand() * rand() % elementsRange - elementsRange / 2;
			}
			sorter->sort(array, cmp);
			QCOMPARE(array.size(), maxSize);
			checkSortedArray();
		}
	}
};
