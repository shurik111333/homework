#pragma once

#include <QtCore/QObject>
#include <QtTest/QtTest>
#include "hashmap.h"
#include "linearhash.h"

class HashmapTest : public QObject
{
	Q_OBJECT

public:
	explicit HashmapTest(QObject *parent = 0):
	    QObject(parent)
	{}

private:
	HashMap *map;

private slots:
	void init()
	{
		map = new HashMap();
	}

	void cleanup()
	{
		delete map;
	}

	void testCountElementsInEmptyMap()
	{
		QCOMPARE(map->count(), 0);
	}

	void testAddElement()
	{
		map->insert("key1", 12);
		QCOMPARE(map->find("key1"), 12);
	}

	void testAddAndCountElements()
	{
		map->insert("key1", 12);
		QCOMPARE(map->count(), 1);
	}

	void testRemoveElement()
	{
		map->insert("key111", 123);
		QCOMPARE(map->find("key111"), 123);
		map->remove("key111", 123);
		QVERIFY_EXCEPTION_THROWN(map->find("key111"), QString);
	}

	void testAddElementsWithEqualKey()
	{
		map->insert("key1", 42);
		QVERIFY_EXCEPTION_THROWN(map->insert("key1", 17), QString);
	}

	void testAddFewElements()
	{
		for (int i = 0; i < 5; i++)
		{
			map->insert(QString("key%0").arg(i), i);
		}
		QCOMPARE(map->count(), 5);
		for (int i = 0; i < 5; i++)
		{
			QCOMPARE(map->find(QString("key%0").arg(i)), i);
		}
	}

	void testAddFewElementsWithChangeHash()
	{
		for (int i = 0; i < 5; i++)
		{
			map->insert(QString("key%0").arg(i), i);
		}
		map->setHashFunction(QSharedPointer<IHash>(new LinearHash()));
		QCOMPARE(map->count(), 5);
		for (int i = 0; i < 5; i++)
		{
			QCOMPARE(map->find(QString("key%0").arg(i)), i);
		}
	}

	void testAddAndClear()
	{
		for (int i = 0; i < 5; i++)
		{
			map->insert(QString("key%0").arg(i), i);
		}
		map->clear();
		QCOMPARE(map->count(), 0);
		for (int i = 0; i < 5; i++)
		{
			QVERIFY_EXCEPTION_THROWN(map->find(QString("key%0").arg(i)), QString);
		}
	}
};
