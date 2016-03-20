#pragma once

#include <QtCore/QObject>
#include <QtTest/QtTest>
#include <cstdlib>
#include <ctime>
#include "ISort.h"

class ISortTest : public QObject
{
	Q_OBJECT

public:
	explicit ISortTest(ISort *sorter, QObject *parent = 0):
	    QObject(parent),
	    sorter(sorter)
	{}

private:
	ISort *sorter;
	int *array;
	const int countRandTest = 1e3;
	const int maxSize = 1e3;
	const int elementsRange = 1e5;

	void checkSortedArray(int length)
	{
		for (int i = 0; i < length - 1; i++)
		{
			QVERIFY(array[i] <= array[i + 1]);
		}
	}

private slots:
	void init()
	{
		array = new int[20];
	}

	void cleanup()
	{
		delete[] array;
	}

	void testOneElement()
	{
		array[0] = 10;
		sorter->sort(array, 1);
		QCOMPARE(array[0], 10);
	}

	void testSortedArray()
	{
		for (int i = 0; i < 10; i++)
		{
			array[i] = i * 2;
		}
		sorter->sort(array, 10);
		checkSortedArray(10);
	}

	void testDecreasingArray()
	{
		for (int i = 0; i < 10; i++)
		{
			array[9 - i] = i * 2;
		}
		sorter->sort(array, 10);
		checkSortedArray(10);
	}

	void randomTests()
	{
		srand(time(0));
		delete[] array;
		array = new int[maxSize];
		for (int i = 0; i < countRandTest; i++)
		{
			int len = rand() % maxSize + 1;
			for (int j = 0; j < len; j++)
			{
				array[j] = rand() % elementsRange - elementsRange / 2;
			}
			sorter->sort(array, len);
			checkSortedArray(len);
		}
	}
};
