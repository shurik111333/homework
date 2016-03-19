#pragma once

#include <QtCore/QObject>
#include <QtTest/QtTest>
#include "IList.h"
#include "ListPointer.h"

class ListPointerTest : public QObject
{
	Q_OBJECT

public:
	explicit ListPointerTest(QObject *parent = 0):
	    QObject(parent)
	{}

private:
	IList<int> *list;

private slots:
	void init()
	{
		list = new ListPointer();
	}

	void cleanup()
	{
		delete list;
	}

	void testEmptyList()
	{
		QCOMPARE(list->length(), 0);
	}

	void testAddElement()
	{
		list->insert(42, 0);
		QCOMPARE((*list)[0], 42);
	}

	void testCountOneElement()
	{
		list->insert(42, 0);
		QCOMPARE(list->length(), 1);
	}

	void testRemoveOneElement()
	{
		list->insert(42, 0);
		QVERIFY(list->remove(42));
		QCOMPARE(list->length(), 0);
	}

	void testFindNonexistingElement()
	{
		list->insert(42, 0);
		QCOMPARE(list->findElementId(15), -1);
	}

	void testRemoveNonexistingElement()
	{
		list->insert(42, 0);
		QVERIFY(!list->remove(20));
	}

	void testAddFewElements()
	{
		for (int i = 0; i < 20; i++)
		{
			list->insert(i + 2, i);
		}
		QCOMPARE(list->length(), 20);
		for (int i = 0; i < 20; i++)
		{
			QCOMPARE((*list)[i], i + 2);
			QCOMPARE(list->findElementId(i + 2), i);
		}
	}

	void testRemoveFewElements()
	{
		for (int i = 0; i < 20; i++)
		{
			list->insert(i + 2, i);
		}
		for (int i = 15; i < 20; i++)
		{
			QVERIFY(list->remove(i + 2));
		}
		QCOMPARE(list->length(), 15);
		for (int i = 0; i < 5; i++)
		{
			QVERIFY(list->remove(i + 2));
		}
		QCOMPARE(list->length(), 10);
		for (int i = 5; i < 15; i++)
		{
			QVERIFY(list->findElementId(i + 2) != -1);
		}
	}
};
