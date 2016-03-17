#pragma once

#include <QtCore/QObject>
#include <QtTest/QtTest>
#include "hashmap.h"

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
		map->removehash();
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
};
